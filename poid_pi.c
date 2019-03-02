#include <stdio.h>
#include "poid_pi.h"
#include "utils.h"

double **creer_distance_tab(Coordonnees c) {
	double **distances = (double **) malloc((sizeof(double *) * c->n));
	Sommet s1, s2; // Indices d'iterations

	for (s1 = 0; s1 < c->n; ++s1) {
		distances[s1] = (double *) malloc(sizeof(double) * c->n);
		for (s2 = 0; s2 < c->n; ++s2) {
			distances[s1][s2] = -1;
		}
	}

	for (s1 = 0; s1 < c->n; ++s1) {
		for (s2 = 0; s2 < c->n; ++s2) {
			if (distances[s1][s2] == -1) {
				distances[s1][s2] = distance(c, s1, s2);
				distances[s2][s1] = distances[s1][s2];
			}
		}
	}

	return distances;
}

void affiche_mat(double **mat, int taille_mat) {
	for (int i = 0; i < taille_mat; ++i) {
		for (int j = 0; j < taille_mat; ++j) {
			printf("%.2lf  ", mat[i][j]);
		}
		printf("\n");
	}
}

void detruire_distance_tab(double ***pDistances, int taille_distances) {
	Sommet i;

	for (i = 0; i < taille_distances; ++i) {
		free((*pDistances)[i]);
	}
	free(*pDistances);
}

double omega_pi(double **distance_tab, double pi[], int s1, int s2) {
	return pi[s1] + pi[s2] + distance_tab[s1][s2];
}

double omega_pi_graphe(Graphe g, double **distance_tab, double pi[]) {
	Sommet s;// Sommet testé
	Sommet *voisin;// Liste des voisins du sommet 's'
	int i;// Indice du voisin
	double omega = 0;// Poid de l'ensemble des arêtes

	for (s = 0; s < graphe_nb_sommets(g); ++s) {
		voisin = g->alist[s]->list;
		for (i = 0; i < graphe_degre(g, s); ++i) {
			if (s < voisin[i]) {//On ne compte omega_pi que si s < voisin[i] pour compter de facon unique le poid de chaque arête
				omega += omega_pi(distance_tab, pi, s, voisin[i]);
			}
		}
	}

	return omega;
}

double t(Graphe g, double **distance_tab, double pi[], double lambda) {
	Sommet s; // Le sommet testé
	double d;// d_i - 2
	double sumD = 0; // Somme pour s des d_i - 2 au carré
	double sumPi = 0; // Somme pour s des pi[s]

	for (s = 0; s < graphe_nb_sommets(g); ++s) {
		d = graphe_degre(g, s) - 2;
		sumD += d * d;
		sumPi += pi[s];
	}
	return lambda * (UB - omega_pi_graphe(g, distance_tab, pi) + 2 * sumPi) / sumD;
}

double pi_s(Sommet s, double *pi, Graphe g, double **distance_tab, double lambda) {
	return pi[s] + t(g, distance_tab, pi, lambda) * (graphe_degre(g, s) - 2);
}

double *construire_nouv_pi(double pi[], Graphe g, double **distance_tab, double lambda) {
	double *nPi = (double *) malloc(sizeof(double) * graphe_nb_sommets(g));// Nouvelle liste de poids
	Sommet s; // Sommet dont on update le poid

	for (s = 0; s < graphe_nb_sommets(g); ++s) {
		nPi[s] = pi_s(s, pi, g, distance_tab, lambda);
	}

	return nPi;
}

Graphe borne_inferieur(Coordonnees c) {
	Graphe g = NULL;// Dernier graphe généré
	Graphe gOld = NULL; // Iteration précédente du graphique
	Sommet s;// Un sommet du graphe
	double **distance_tab = creer_distance_tab(c);// Matrice des distances entre sommets
	double *pi = (double *) malloc(sizeof(double) * c->n);// Derniers poids calculés
	double *piOld = NULL;// Itération précédente des poids
	double lambda = 2.;
	double longueur; // Longueur du parcourt
	int iter = 0; // Compteur d'iteration
	int nextUpdate = 2 * c->n;// Nombre d'itérations avant mise à jour
	int updateIter = nextUpdate;// Itération de mise a jour

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

	/* Libération de la mémoire */
	if (gOld != NULL) { detruire_graphe(gOld); }
	if (piOld != NULL) { free(piOld); }
	if (pi != NULL) { free(pi); }
	if (distance_tab != NULL) { detruire_distance_tab(&distance_tab, c->n); }

	return g;
}