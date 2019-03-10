#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#ifndef UNION_FIND_H
#define UNION_FIND_H
typedef struct union_find{
int nMax;
size_t* parent;
} Union_find;

/**
 * Création de la structure de donnée union-find
 *
 * @param nMax le nombre d'élément maximal
 * @return Union_find avec nMax sommets indépendants
 */
Union_find* uf_init(int nMax);

/**
 * Unie deux sommets dans l'union-find
 *
 * @param x et y deux sommets à unir
 * @param uf Union_find
 */
void uf_union(Union_find* uf, size_t x,size_t y);

/**
 * Retourne le sommet 'racine' du sommet x
 *
 * @param x sommet dont on cherche la racine
 * @param uf Union_find
 * @return size_t racine du sommet
 */
size_t uf_find(Union_find* uf, size_t x);

/**
 * Detruit l'union_find'
 *
 * @param uf Union_find
 */
void uf_free(Union_find* uf);

/**
 * Verifie si rajouter une arete entre x et  forme un cycle
 *
 * @param x et y sommets qu'on étudie
 * @param uf Union_find
 * @return bool si ajouter une arete forme un cycle
 */
bool uf_cycle(Union_find* uf, size_t x,size_t y);
#endif
