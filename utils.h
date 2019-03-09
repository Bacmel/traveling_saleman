#include "graph.h"
#include<stdbool.h>
#include<stdlib.h>

#ifndef UTILS_H
#define UTILS_H

#define DEBUG_MODE 0

/**
 * Calcul la distance entre deux sommets
 *
 * @param c Coordonnées de tous les sommets (doit au moins comprendre s1 et s2)
 * @param s1 Un sommet
 * @param s2 Un sommet
 * @return distance euclidienne entre les sommets s1 et s2
 */
double distance(Coordonnees c, int s1, int s2);

/**
 * Calcule les distances des points entre eux et les met dans une matrice de taille (c->n)²
 *
 * @param coordonnees Coordonnées des points
 * @return Matrice des distances entre tous les points
 */
double **creer_distance_tab(Coordonnees coordonnees);

/**
 * Affiche une matrice carrée dans la console
 *
 * @param mat Matrice a afficher
 * @param taille_mat Taille de la matrice
 */
void affiche_mat(double **mat, int taille_mat);

/**
 * Detruit la matrice des distances
 *
 * @param pDistances Un pointeur vers la matrice des distances
 * @param taille_distances Taille de la matrice des distances
 */
void detruire_distance_tab(double ***pDistances, int taille_distances);

/**
 * Prédicat de la présence de l'élément i dans le tableau tab
 *
 * @param tab Tableau à tester (peut être NULL)
 * @param n Taille du tableau
 * @param i Elément à chercher
 * @return 'true' si l'élément est présent au moins une fois, 'false' sinon
 */
bool est_present(int *tab, int n, int i);

#endif