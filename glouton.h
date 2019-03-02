#ifndef GLOUTON_H
#define GLOUTON_H
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "union_find.h"
#include "graph.h"

typedef struct arete{
    size_t s1, s2;
    double dist;
} Arete;

Arete* creation_arete(Coordonnees c);
void fusion(Arete* a, Arete* a1, int n1, Arete* a2, int n2);
Arete* tri_fusion_arete(Arete* a, int n);
void detruire_arete(Arete* a);
Graphe algo(Coordonnees c);

#endif
