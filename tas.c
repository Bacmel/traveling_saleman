#include <stdlib.h>
#include <math.h>
#include "tas.h"

Tas creer_tas(int taille){
	Tas t = (Tas) malloc(sizeof(struct tas));
	t->maxTaille = taille;
	t->elems = (int *) malloc(sizeof(int) * (taille + 1));
	t->val = (double *) malloc(sizeof(double) * (taille + 1));
	t->pos = (int *) malloc(sizeof(int) * (taille + 1));
	
	t->elems[0] = 0;
	t->val[0] = 0;
	t->pos[0] = 0;
}
void detruire_tas(Tas * pTas){
	free((*pTas)->elems);
	free((*pTas)->val);
	free((*pTas)->pos);
	free(*pTas);
}
void tas_echanger(Tas t, int pos1, int pos2){
	int temp = t->elems[pos1]; // Echange des éléments
	t->elems[pos1] = t->elems[pos2];
	t->elems[pos2] = temp;
	
	double tempV = t->val[pos1]; // Echange des valeurs
	t->val[pos1] = t->val[pos2];
	t->val[pos2] = tempV;
	
	t->pos[t->elems[pos1]] = pos1; // Mise a jour des positions
	t->pos[t->elems[pos2]] = pos2;
}

void tas_monter(Tas t, int s) {
	int posS = t->pos[s];
	if(t->val[posS / 2] > t->val[posS] && posS > 1) {
		tas_echanger(t, posS, posS / 2); 
	}
}

void tas_descendre(Tas t, int s) {
	int posS = t->pos[s];
	if(t->val[posS * 2] < t->val[posS] && posS * 2 <= t->elems[0]){
		tas_echanger(t, posS, posS * 2);
	} else if (t->val[posS * 2 + 1] < t->val[posS] && posS * 2 + 1 <= t->elems[0]) {
		tas_echanger(t, posS, posS * 2 + 1);
	}
}

void tas_inserer(Tas t, int s, Coordonnees c) {
	double sX = c->clist[s]->coordx;
	double sY = c->clist[s]->coordy;
	double value = sqrt(sX * sX + sY * sY);
	
	t->elems[t->elems[0]] = s;
	t->val[t->elems[0]] = value;
	t->pos[s] = t->elems[0]++;
	
	tas_monter(t, s);
}

void tas_retirer(Tas t, int s){
	tas_echanger(t, t->pos[s], t->elems[0]--);
	
	tas_descendre(t, s);
}

int tas_retirer_tete(Tas t){
	int s = t->elems[1];
	
	tas_retirer(t, s);
	
	return s;
}
