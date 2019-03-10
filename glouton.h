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

/**
 * Creation de la structure de donné Arete
 *
 * @param c Coordonnees des differents sommets
 * @return Arete* le tableau de toutes les aretes possibles de c
 */
Arete* creation_arete(Coordonnees c);

/**
 * Intercalement du contenue de a1 et a2 dans le tableau a
 *
 * @param a1 et a2 les tableau d'aretes trié de taille n1 et n2
 * @param a le tableau de la fusion de a1 et a2 de taille n1+n2
 */
void fusion(Arete* a, Arete* a1, int n1, Arete* a2, int n2);

/**
 * Retourne le tableau des aretes trié par longueur croissantes avec la méthode du trie fusion
 *
 * @param a le tableau à trier
 * @param n la taille de a
 * @return un tableau d'arete trié
 */
Arete* tri_fusion_arete(Arete* a, int n);

/**
 * Retourne le tableau des aretes trié par longueur croissantes avec la méthode du trie fusion
 *
 * @param a le tableau à trier
 * @param n la taille de a
 * @return un tableau d'arete trié
 */
void detruire_arete(Arete* a);

/**
 * Création d'un hamiltonien à partir d'un graphe supposé etre un cycle
 *
 * @param g Graphe en forme de cycle
 * @return Hamiltonien
 */
Hamiltonien* creation_hamiltonien(Graphe g);

/**
 * Change l'Hamiltonien en échangeant deux aretes
 *
 * @param i et i2 les Sommets de la premiere arete
 * @param j et j2 les Sommets de la deuxieme arete
 * @param H l'Hamiltonien
 */
void change_hamiltonien(Hamiltonien* H, size_t i, size_t i2, size_t j, size_t j2);

/**
 * Detruit la structure Hamiltonien
 *
 * @param Hamiltonien
 */
void detruire_hamiltonien(Hamiltonien* H);


/**
 * Algorithme glouton (insère les aretes par valeurs croissantes tant qu'elles ne font pas de cycle et que les degrés des sommets <2)
 *
 * @param c Coordonnees
 * @return Graphe 
 */
Graphe algo(Coordonnees c);

/**
 * Algorithme glouton + Implementation de l'algorithme 2-opt
 *
 * @param c Coordonnees
 * @return Graphe 
 */
Graphe algo2opt(Coordonnees c);

/**
 * Algorithme glouton + Implementation de l'algorithme du recuit simulé
 *
 * @param c Coordonnees
 * @return Graphe 
 */
Graphe resim(Coordonnees c);

#endif
