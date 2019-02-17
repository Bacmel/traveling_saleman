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

Tas creer_tas(int taille); // Crée un tas de taille maximale 'size'
void detruire_tas(Tas *pTas); // Libère un tas de la mémoire
void tas_inserer(Tas t, int s, double valeur); // Insere l'élément 's' dans le tas relativement au point 'sCourant' pour le calcul des distances
void tas_update(Tas t, int s, double newValeur); // Met à jour la valeur de l'élément 's' du Tas 't'
void tas_retirer(Tas t, int s);// Retire l'élément 's' du tas
int tas_retirer_tete(Tas t); // Retire la tête du tas et retourne son identifiant
void tas_afficher(Tas t);

int tas_taille(Tas t);

#endif
