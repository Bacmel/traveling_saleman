#ifndef TAS_H
#define TAS_H

#include "graph.h"

struct tas {
	int maxTaille; // Taille maximale du tas
	int * elems; // Liste des sites
	double * val; // Distance (valeur)
	int * pos; // Position du site dans le tas
};

typedef struct tas * Tas;

Tas creer_tas(int taille); // Crée un tas de taille maximale 'size'
void detruire_tas(Tas * pTas); // Libère un tas de la mémoire
void tas_inserer(Tas t, int s, Coordonnees c);// Insere l'élément 's' dans le tas
void tas_retirer(Tas t, int s);// Retire l'élément 's' du tas
int tas_retirer_tete(Tas t); // Retire la tête du tas et retourne son identifiant
#endif
