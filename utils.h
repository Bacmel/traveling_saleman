#include "graph.h"
#include<stdbool.h>
#include<stdlib.h>

#ifndef UTILS_H
#define UTILS_H
/* Calcul la distance entre deux sommets 's1' et 's2' */
double distance(Coordonnees c, int s1, int s2);
bool est_present(int* tab, int n, int i);
Graphe graph1arbre(Coordonnees c, int s);
double score(Coordonnees c, double pi[], int s1, int s2);
Graphe graph1arbre_pi(Coordonnees c, int s, double pi[], int taillePi);
void a_remove(int *tab, int n, int s);
void graphe_supprimer_arete(Graphe g, int s1, int s2);
#endif
