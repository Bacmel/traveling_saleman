#ifndef _1ARBRE_H
#define _1ARBRE_H

#include "graph.h"

/**
 * Construit un 1-arbre optimale avec 's' le sommet à l'origine du cycle
 *
 * @param c Coordonnées de tous les sommets du graphe à construire
 * @param s Sommet à l'origine du cycle
 * @return un 1-arbre optimale avec 's' le sommet à l'origine du cycle
 */
Graphe graph1arbre(Coordonnees c, Sommet s, double **mat_distances);

/**
 * Construit un 1-arbre optimale avec 's' le sommet à l'origine du cycle à partir du graphe doté des poids pi
 *
 * @param c Coordonnées de tous les sommets du graphe à construire
 * @param s Sommet à l'origine du cycle
 * @param pi Tableau des poid de chaque sommet
 * @param taillePi Taille du tableau des poids de chaque sommet
 * @return un 1-arbre optimale avec 's' le sommet à l'origine du cycle à partir du graphe doté des poids pi
 */
Graphe graph1arbre_pi(Coordonnees c, Sommet s, double **mat_distances, double pi[]);

#endif //1ARBRE_H
