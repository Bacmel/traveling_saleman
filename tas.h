#ifndef TAS_H
#define TAS_H
#include "
struct tas {
	int maxTaille; // Taille maximale du tas
	int * elems; // Liste des sites
	double * val; // Distance (valeur)
	int * pos; // Position du site dans le tas
};

typedef struct tas * Tas;

Tas creer_tas(int taille); // Crée un tas de taille maximale 'size'
void detruire_tas(Tas * pTas); // Libère un tas de la mémoire
void tas_insert(Tas t, int s, Coordonnees c);
#endif
