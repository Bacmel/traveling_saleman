#include <math.h>
#include <stdio.h>
#include "utils.h"
#include "prim.h"

double distance(Coordonnees c, int s1, int s2) {
	struct coord *s1Coord = c->clist[s1];
	struct coord *s2Coord = c->clist[s2];
	return sqrt(pow(s1Coord->coordx - s2Coord->coordx, 2) + pow(s1Coord->coordy - s2Coord->coordy, 2));
}

double **creer_distance_tab(Coordonnees coordonnees) {
	double **distances = (double **) malloc((sizeof(double *) * coordonnees->n));
	Sommet s1, s2; // Indices d'iterations

	for (s1 = 0; s1 < coordonnees->n; ++s1) {
		distances[s1] = (double *) malloc(sizeof(double) * coordonnees->n);
		for (s2 = 0; s2 < coordonnees->n; ++s2) {
			distances[s1][s2] = -1;
		}
	}

	for (s1 = 0; s1 < coordonnees->n; ++s1) {
		for (s2 = 0; s2 < coordonnees->n; ++s2) {
			if (distances[s1][s2] == -1) {
				distances[s1][s2] = distance(coordonnees, s1, s2);
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

Graphe graph1arbre(Coordonnees c, int s) {
	Graphe g = prim_exclu(c, &s, 1);// Construction de l'arbre optimal sur le sous graph excluant uniquement 's'
	Tas t = creer_tas(c->n);
	int i;

	for (i = 0; i < c->n; i++) {
		if (i == s) { continue; }// On ignore le sommet hors de l'arbre
		tas_inserer(t, i, distance(c, i, s));
	}

	for (i = 0; i < 2; i++) {
		graphe_ajouter_arete(g, s, tas_retirer_tete(t)); // Ajout des 2 arretes de valeurs minimales
	}

	detruire_tas(&t);
	return g;
}

double score(Coordonnees c, double pi[], int s1, int s2) {
	double score = distance(c, s1, s2);
	if (pi != NULL) { score += pi[s1] + pi[s2]; }
	return score;
}

Graphe graph1arbre_pi(Coordonnees c, int s, double pi[], int taillePi) {
	Graphe graphe = prim_exclu_pi(c, &s, 1, pi);
	Tas tas = creer_tas(c->n);
	int s_i;
	int i;

	for (s_i = 0; s_i < c->n; s_i++) {
		if (s_i == s) { continue; }
		tas_inserer(tas, s_i, score(c, pi, s_i, s));
	}

	for (i = 0; i < 2; i++) {
		graphe_ajouter_arete(graphe, s, tas_retirer_tete(tas));
	}

	detruire_tas(&tas);
	return graphe;
}