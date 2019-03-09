#ifndef TAS_H
#define TAS_H

#include "graph.h"

struct tas {
	int maxTaille; // Taille maximale du tas
	int *elems; // Liste des sites
	double *val; // Distance (valeur)
	int *pos; // Position du site dans le tas
};

typedef struct tas *Tas;

/**
 * Crée un tas de taille maximale 'taille'
 *
 * @param taille Le nombre maximum d'élément et leur identifiant maximum
 * @return Un tas pouvant accueillir 'taille' éléments d'identifiant <= taille
 */
Tas creer_tas(int taille);

/**
 * Détruit un tas de la mémoire
 *
 * @param pTas Pointeur vers le tas à détruire
 */
void detruire_tas(Tas *pTas);

/**
 * Insère l'élément 's' dans le tas relativement au point 'sCourant' pour le calcul des distances
 *
 * @param t La tas auquel on va ajouter le sommet
 * @param s Le sommet à insérer
 * @param valeur Le poid du sommet à insérer
 */
void tas_inserer(Tas t, Sommet s, double valeur);

/**
 * Met à jour la valeur de l'élément 's' du Tas 't'
 *
 * @param t La tas auquel on va mettre à jour le sommet
 * @param s Le somment à mettre à jour
 * @param newValeur Nouveau poid du sommet
 */
void tas_update(Tas t, Sommet s, double newValeur);

/**
 * Retire l'élément 's' du tas
 *
 * @param t Tas dont on va retirer un sommet
 * @param s Sommet à retirer
 */
void tas_retirer(Tas t, Sommet s);

/**
 * Retire la tête du tas et retourne son identifiant
 *
 * @param t Tas dont on va retirer la tête
 * @return L'identifiant de la tête retirée
 */
int tas_retirer_tete(Tas t);

/**
 * Affiche le tas dans la console
 *
 * @param t Tas à afficher
 */
void tas_afficher(Tas t);

/**
 * Donne la taille du tas
 *
 * @param t Tas dont on désire connaitre la taille
 * @return La taille du tas
 */
int tas_taille(Tas t);

#endif
