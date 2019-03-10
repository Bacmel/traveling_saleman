#ifndef PRIM_H
#define PRIM_H

#include"tas.h"
#include"graph.h"
#include"utils.h"

Graphe prim(Coordonnees c, double **distances_mat);

Graphe prim_exclu(Coordonnees c, double **distances_mat, Sommet exclus[], int tailleExclus);

Graphe prim_exclu_pi(Coordonnees c, double **distances_mat, Sommet exclus[], int tailleExclus, double pi[]);

#endif
