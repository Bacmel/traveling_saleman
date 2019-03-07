#include "graph.h"
#include<stdbool.h>
#include<stdlib.h>

#ifndef UTILS_H
#define UTILS_H

/* Calcul la distance entre deux sommets 's1' et 's2' */
double distance(Coordonnees c, int s1, int s2);

/**
 * Calcule les distances des points entre eux et les met dans une matrice de taille c->n²
 * @param coordonnees Coordonnées des points
 * @return Matrice des distances entre tous les points
 */
double **creer_distance_tab(Coordonnees coordonnees);

void affiche_mat(double **mat, int taille_mat);

/**
 * Detruit le tableau des distances
 * @param pDistances Un pointeur vers la matrice des distances
 * @param taille_distances Taille de la matrice des distances
 */
void detruire_distance_tab(double ***pDistances, int taille_distances);

bool est_present(int *tab, int n, int i);

Graphe graph1arbre(Coordonnees c, int s);

double score(Coordonnees c, double pi[], int s1, int s2);

Graphe graph1arbre_pi(Coordonnees c, int s, double pi[], int taillePi);

#endif
