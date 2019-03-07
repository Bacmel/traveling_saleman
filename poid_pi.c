#include <stdio.h>
#include "poid_pi.h"
#include "utils.h"
#include "1arbre.h"


double omega_pi(double **distance_tab, double pi[], int s1, int s2) {
	double poid = distance_tab[s1][s2];
	if (pi != NULL) { poid += pi[s1] + pi[s2]; }
	return poid;
}

double omega_pi_graphe(Graphe graphe, double **distance_tab, double pi[]) {
	Sommet s;// Sommet testé
	Sommet *voisin;// Liste des voisins du sommet 's'
	int i;// Indice du voisin
	double omega = 0;// Poid de l'ensemble des arêtes

	for (s = 0; s < graphe_nb_sommets(graphe); ++s) {
		voisin = graphe->alist[s]->list;
		for (i = 0; i < graphe_degre(graphe, s); ++i) {
			if (s < voisin[i]) {//On ne compte omega_pi que si s < voisin[i] pour compter de facon unique le poid de chaque arête
				omega += omega_pi(distance_tab, pi, s, voisin[i]);
			}
		}
	}

	return omega;
}

double t(Graphe graphe, double **distance_tab, double pi[], double lambda, double ub) {
	Sommet s; // Le sommet testé
	double d; // d_i - 2
	double sumD = 0; // Somme pour s des d_i - 2 au carré
	double sumPi = 0; // Somme pour s des pi[s]

	for (s = 0; s < graphe_nb_sommets(graphe); ++s) {
		d = graphe_degre(graphe, s) - 2;
		sumD += d * d;
		sumPi += pi[s];
	}

	return lambda * (ub - omega_pi_graphe(graphe, distance_tab, pi) + 2 * sumPi) / sumD;
}

double pi_s(Sommet sommet, double *pi, Graphe graphe, double t) {
	return pi[sommet] + t * (graphe_degre(graphe, sommet) - 2);
}

double *construire_nouv_pi(double pi[], Graphe graphe, double **distance_tab, double lambda, double ub) {
	double *nPi = (double *) malloc(sizeof(double) * graphe_nb_sommets(graphe));// Nouvelle liste de poids
	double coef_t = t(graphe, distance_tab, pi, lambda, ub);
	Sommet s; // Sommet dont on update le poid

	for (s = 0; s < graphe_nb_sommets(graphe); ++s) {
		nPi[s] = pi_s(s, pi, graphe, coef_t);
	}

	return nPi;
}

Graphe borne_inferieur(Coordonnees coordonnees, double ub) {
	Graphe graphe = NULL;// Dernier graphe généré
	Graphe graphe_old = NULL; // Iteration précédente du graphique
	Sommet s;// Un sommet du graphe
	double **distance_tab = creer_distance_tab(coordonnees);// Matrice des distances entre sommets
	double *pi = (double *) malloc(sizeof(double) * coordonnees->n);// Derniers poids calculés
	double *pi_old = NULL;// Itération précédente des poids
	double lambda = 2.;
	double longueur; // Longueur du parcourt
	int iter = 0; // Compteur d'iteration
	int nextUpdate = 2 * coordonnees->n;// Nombre d'itérations avant mise à jour
	int updateIter = nextUpdate;// Itération de mise a jour

	for (s = 0; s < coordonnees->n; s++) { pi[s] = 0; }// initialisation du tableau pi à 0

	while (nextUpdate > 1) {
		printf("Tour %d\n", iter);
		if (graphe_old != NULL) { detruire_graphe(graphe_old); }
		graphe_old = graphe;
		graphe = graph1arbre_pi(coordonnees, 0, distance_tab, pi);
		if (pi_old != NULL) { free(pi_old); }
		pi_old = pi;
		pi = construire_nouv_pi(pi_old, graphe, distance_tab, lambda, ub);

		if (iter == updateIter) {
			lambda /= 2;
			nextUpdate /= 2;
			updateIter += nextUpdate;
			printf("update de lambda! lambda= %lf, nextUpdate = %d\n", lambda, nextUpdate);
		}
		iter++;
	}

	if (pi_old != NULL) {
		longueur = omega_pi_graphe(graphe, distance_tab, pi_old);
		printf("Omega_pi(graphe) = %lf\npi : ", longueur);
		for (s = 0; s < coordonnees->n; ++s) {
			longueur -= 2 * pi_old[s];
			printf("%lf, ", pi_old[s]);
		}
		printf("\nScore atteint: %lf\n", longueur);
	}

	/* Libération de la mémoire */
	if (graphe_old != NULL) { detruire_graphe(graphe_old); }
	if (pi_old != NULL) { free(pi_old); }
	if (pi != NULL) { free(pi); }
	if (distance_tab != NULL) { detruire_distance_tab(&distance_tab, coordonnees->n); }

	return graphe;
}