#ifndef PRIM_H
#define PRIM_H

#include"tas.h"
#include"graph.h"
#include"utils.h"

Graphe prim(Coordonnees c);

Graphe prim_exclu(Coordonnees c, Sommet exclus[], int tailleExclus);

Graphe prim_exclu_pi(Coordonnees c, Sommet exclus[], int tailleExclus, double pi[]);

#endif
