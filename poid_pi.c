#include <stdio.h>
#include "poid_pi.h"
#include "utils.h"

double **creer_distance_tab(Coordonnees c) {
	double **distances = (double **) malloc((sizeof(double *) * c->n));
	int i, j; // Indices d'iterations

	for (i = 0; i < c->n; ++i) {
		distances[i] = (double *) malloc(sizeof(double) * c->n);
		for (j = 0; j < c->n; ++j) {
			distances[i][j] = -1;
		}
	}

	for (i = 0; i < c->n; ++i) {
		for (j = 0; j < c->n; ++j) {
			if (distances[i][j] == -1) {
				distances[i][j] = distance(c, i, j);
				distances[j][i] = distances[i][j];
			}
		}
	}

	return distances;
}

void detruire_distance_tab(double ***pDistances, int n) {
	int i;

	for (i = 0; i < n; ++i) {
		free((*pDistances)[i]);
	}
	free(*pDistances);
}

double omega_pi(double **distance_tab, double pi[], int s1, int s2) {
	return pi[s1] + pi[s2] + distance_tab[s1][s2];
}

double omega_pi_graphe(Graphe g, double **distance_tab, double pi[]) {
	int i, j;
	struct voisins *voisin;
	double omega = 0;

	for (i = 0; i < graphe_nb_sommets(g); ++i) {
		voisin = g->alist[i];
		for (j = 0; j < graphe_degre(g, i); ++j) {
			if (i < voisin->list[j]) {//On ne compte omega_pi que si i < j pour compter de facon unique le poid de chaque arete
				omega += omega_pi(distance_tab, pi, i, voisin->list[j]);
			}
		}
	}
	return omega;
}

double t(Graphe g, double **distance_tab, double pi[], double lambda) {
	double sumD = 0; // Somme pour i des d_i - 2 au carré
	double sumPi = 0; // Somme pour i des pi[i]
	double d;// d_i - 2
	int i;
	for (i = 0; i < graphe_nb_sommets(g); ++i) {
		d = graphe_degre(g, i) - 2;
		sumD += d * d;
		sumPi += pi[i];
	}
	return lambda * (UB - omega_pi_graphe(g, distance_tab, pi) + 2 * sumPi) / sumD;
}

double pi_s(int s, double *pi, Graphe g, double **distance_tab, double lambda) {
	return pi[s] + t(g, distance_tab, pi, lambda) * (graphe_degre(g, s) - 2);
}

double *construire_nouv_pi(double pi[], Graphe g, double **distance_tab, double lambda) {
	double *nPi = (double *) malloc(sizeof(double) * graphe_nb_sommets(g));
	int i;

	for (i = 0; i < graphe_nb_sommets(g); ++i) {
		nPi[i] = pi_s(i, pi, g, distance_tab, lambda);
	}

	return nPi;
}

void affiche_mat(double **mat, int tailleMat) {
	for (int i = 0; i < tailleMat; ++i) {
		for (int j = 0; j < tailleMat; ++j) {
			printf("%.2lf  ", mat[i][j]);
		}
		printf("\n");
	}
}

Graphe borneInferieur(Coordonnees c) {
	Graphe g = NULL, gOld = NULL;
	double **distance_tab = creer_distance_tab(c);
	double *pi = (double *) malloc(sizeof(double) * c->n), *piOld = NULL;
	double lambda = 2.;
	double longueur = 0.;
	int iter = 0; // compteur d'iteration
	int nextUpdate = 2 * c->n;//nombre d'iterations avant mise a jour
	int updateIter = nextUpdate;//iteration de mise a jour
	int s;//un sommet du graphe

	for (s = 0; s < c->n; s++) { pi[s] = 0; }// initialisation du tableau pi à 0

	while (nextUpdate > 1) {
		printf("Tour %d\n", iter);
		if (gOld != NULL) { detruire_graphe(gOld); }
		gOld = g;
		g = graph1arbre_pi(c, 0, pi, c->n);
		if (piOld != NULL) { free(piOld); }
		piOld = pi;
		pi = construire_nouv_pi(piOld, g, distance_tab, lambda);

		if (iter == updateIter) {
			lambda /= 2;
			nextUpdate /= 2;
			updateIter += nextUpdate;
			printf("update de lambda! lambda= %lf, nextUpdate = %d\n", lambda, nextUpdate);
		}
		iter++;
	}
	if (piOld != NULL) {
		longueur = omega_pi_graphe(g, distance_tab, piOld);
		printf("Omega_pi(g) = %lf\npi : ", longueur);
		for (s = 0; s < c->n; ++s) {
			longueur -= 2 * piOld[s];
			printf("%lf, ", piOld[s]);
		}
		printf("\nScore atteint: %lf\n", longueur);
	}
	printf("iter= %d\n", iter);
	/* Libération de la mémoire */
	if (gOld != NULL) { detruire_graphe(gOld); }
	if (piOld != NULL) { free(piOld); }
	if (pi != NULL) { free(pi); }
	if (distance_tab != NULL) { detruire_distance_tab(&distance_tab, c->n); }

	return g;
}


/*Graphe opt(Coordonnees c) {
	double lambda = 2;
	double **distance_tab = creer_distance_tab(c);
	double score = 0;
	int iter = 0, nextChg = 2 * c->n, deltaIter = 2 * c->n;
	double *pi = (double *) malloc(sizeof(double) * c->n);
	double *temp;
	int i;
	double sumPi = 0;
	Graphe g = NULL, oldG;
	affiche_mat(distance_tab, c->n);
	for (i = 0; i < c->n; ++i) {
		pi[i] = 0;
	}

	while (deltaIter >= 1) {
		printf("\n Iteration %d\n", iter);
		oldG = g;
		g = graph1arbre_pi(c, 0, pi, c->n);
		score = omega_pi_graphe(g, distance_tab, pi);
		for (i = 0; i < c->n; ++i) {
			sumPi += pi[i];
			printf("pi[%d] = %.2lf \t sumPi = %.2lf\n", i, pi[i], sumPi);
		}
		printf("sumPi = %.2lf\n", sumPi);
		score = score - (2 * sumPi);
		temp = construire_nouv_pi(pi, c->n, g, distance_tab, lambda);
		free(pi);
		if (oldG != NULL) { free(oldG); }
		pi = temp;
		if (iter == nextChg) {
			deltaIter /= 2;
			nextChg += deltaIter;
			lambda /= 2;
		}
		iter++;
	}
	printf("deltaIter=%d, iter=%d, nextChg=%d\n", deltaIter, iter, deltaIter);
	printf("score = %lf\n", score);
	detruire_distance_tab(&distance_tab, c->n);
	free(pi);

	return g;
}*/