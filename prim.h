#ifndef PRIM_H
#define PRIM_H
#include"tas.h"
#include"graph.h"
#include"utils.h"

Graphe prim(Coordonnees c);
Graphe prim_exclu(Coordonnees c, int* tab, int n);

#endif
