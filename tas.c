#include <stdlib.h>
#include <stdio.h>
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
	
	return t;
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
	int taille = t->elems[0];
	int pos = posS * 2;
	//printf("rec descendre %d %d\n",posS, taille);
	if(pos > taille) { return; } // Pas de fils gauche donc pas de droit non plus
	double minVal = t->val[pos];
	if(pos + 1 <= taille && t->val[pos+1] < minVal) {
		pos++;
	}
	//printf("%lf \t %lf\n", minVal, t->val[posS]);
	if(minVal < t->val[posS]){
		tas_echanger(t, pos, posS);
		tas_descendre(t, posS);
	}
}

void tas_inserer(Tas t, int s, Coordonnees c) {
	double sX = c->clist[s]->coordx;
	double sY = c->clist[s]->coordy;
	double value = sqrt(sX * sX + sY * sY);
	int taille = ++t->elems[0];

	t->elems[taille] = s;
	t->val[taille] = value;
	t->pos[s] = taille;
	
	tas_monter(t, s);
}

void tas_retirer(Tas t, int s){
	int pos = t->pos[s];
	tas_echanger(t, pos, t->elems[0]);
	t->elems[0]--;
	tas_descendre(t, t->elems[pos]);
}

int tas_retirer_tete(Tas t){
	int s = t->elems[1];
	
	tas_retirer(t, s);
	
	return s;
}

void tas_afficher(Tas t){
	printf("Affichage du tas comportant %d / %d elements:\n", t->elems[0], t->maxTaille);
	int pow2 = 1;
	int i;
	for(i = 1; i <= t->elems[0]; i++) {
		printf("%d:%lf\t", t->elems[i], t->val[i]);
		if(i == pow2) {
			printf("\n");
			pow2 = 2*pow2 +1;
		}
	}
	printf("\n");
}

int tas_taille(Tas t){
	return t->elems[0];	
}
