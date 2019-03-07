#include <math.h>
#include <stdio.h>
#include "utils.h"
#include "prim.h"

double distance(Coordonnees c, int s1, int s2) {
	struct coord *s1Coord = c->clist[s1]; // Coordonnées du sommet 1
	struct coord *s2Coord = c->clist[s2]; // Coordonnées du sommet 2

	return sqrt(pow(s1Coord->coordx - s2Coord->coordx, 2) + pow(s1Coord->coordy - s2Coord->coordy, 2));
}

double **creer_distance_tab(Coordonnees coordonnees) {
	double **distances = (double **) malloc((sizeof(double *) * coordonnees->n)); // Matrice des distances
	Sommet s1, s2; // Indices d'iterations

	for (s1 = 0; s1 < coordonnees->n; ++s1) {
		distances[s1] = (double *) malloc(sizeof(double) * coordonnees->n);
		for (s2 = 0; s2 < coordonnees->n; ++s2) {
			distances[s1][s2] = -1;// Initialisation des valeurs à -1
		}
	}
	for (s1 = 0; s1 < coordonnees->n; ++s1) {
		for (s2 = 0; s2 < coordonnees->n; ++s2) {
			if (distances[s1][s2] == -1) { // Calcul de la distance s'il n'est pas déjà fait
				distances[s1][s2] = distance(coordonnees, s1, s2);
				distances[s2][s1] = distances[s1][s2];// La matrice étant symétrique, on peut remplir le symétrique
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

bool est_present(int *tab, int n, int i) {
	if (tab == NULL) { return false; }

	int j;
	for (j = 0; j < n; j++) {
		if (tab[j] == i) {
			return true;
		}
	}
	return false;
}