#ifndef GLOUTON_H
#define GLOUTON_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utils.h"
#include "union_find.h"
#include "graph.h"

typedef struct arete{
    size_t s1, s2;
    double dist;
} Arete;

typedef struct hamiltonien{
    int n;
    size_t* pred;
    size_t* succ;
} Hamiltonien;

Arete* creation_arete(Coordonnees c);
void fusion(Arete* a, Arete* a1, int n1, Arete* a2, int n2);
Arete* tri_fusion_arete(Arete* a, int n);
void detruire_arete(Arete* a);
Hamiltonien* creation_hamiltonien(Graphe g);
void change_hamiltonien(Hamiltonien* H, size_t i, size_t i2, size_t j, size_t j2);
void detruire_hamiltonien(Hamiltonien* H);
Graphe algo(Coordonnees c);
Graphe algo2opt(Coordonnees c);
Graphe resim(Coordonnees c);

#endif
