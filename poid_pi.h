#ifndef POID_PI_H
#define POID_PI_H

#include "graph.h"
#include "utils.h"

#define UB 7542


/**
 * Calcule les distances des points entre eux et les met dans une matrice de taille c->n²
 * @param c Coordonnées des points
 * @return Matrice des distances entre tous les points
 */
double **creer_distance_tab(Coordonnees c);

void affiche_mat(double **mat, int taille_mat);

/**
 * Detruit le tableau des distances
 * @param pDistances Un pointeur vers la matrice des distances
 * @param taille_distances Taille de la matrice des distances
 */
void detruire_distance_tab(double ***pDistances, int taille_distances);

double omega_pi(double **distance_tab, double pi[], Sommet s1, Sommet s2);

double omega_pi_graphe(Graphe g, double **distance_tab, double pi[]);

double t(Graphe g, double **distance_tab, double pi[], double lambda);

double pi_s(Sommet s, double pi[], Graphe g, double **distance_tab, double lambda);

double *construire_nouv_pi(double pi[], Graphe g, double **distance_tab, double lambda);

Graphe borne_inferieur(Coordonnees c);

#endif //POID_PI_H
