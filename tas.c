#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tas.h"

Tas creer_tas(int taille) {
	Tas t = (Tas) malloc(sizeof(struct tas));
	t->maxTaille = taille;
	t->elems = (int *) malloc(sizeof(int) * (taille + 1));
	t->val = (double *) malloc(sizeof(double) * (taille + 1));
	t->pos = (int *) malloc(sizeof(int) * (taille + 1));

	int i;
	for(i = 0; i < taille; i++) {
		t->elems[i] = -1;
		t->val[i] = -1;
		t->pos[i] = -1;
	}
	t->elems[0] = 0;
	return t;
}

void detruire_tas(Tas *pTas) {
	free((*pTas)->elems);
	free((*pTas)->val);
	free((*pTas)->pos);
	free(*pTas);
}

void tas_echanger(Tas t, int pos1, int pos2) {
	//printf("echange pos1 = %d\tpos2 = %d\n", pos1, pos2);
	//printf("\tpos1(%d,%lf,%d)\tpos2(%d,%lf,%d)\n",t->elems[pos1],t->val[pos1],t->pos[t->elems[pos1]], t->elems[pos2],t->val[pos2],t->pos[t->elems[pos2]]);
	int temp = t->elems[pos1]; // Echange des éléments
	t->elems[pos1] = t->elems[pos2];
	t->elems[pos2] = temp;

	double tempV = t->val[pos1]; // Echange des valeurs
	t->val[pos1] = t->val[pos2];
	t->val[pos2] = tempV;

	t->pos[t->elems[pos1]] = pos1; // Mise a jour des positions
	t->pos[t->elems[pos2]] = pos2;
	//printf("\tpos1(%d,%lf,%d)\tpos2(%d,%lf,%d)\n",t->elems[pos1],t->val[pos1],t->pos[t->elems[pos1]], t->elems[pos2],t->val[pos2],t->pos[t->elems[pos2]]);
}

void tas_monter(Tas t, int s) {
	int posS = t->pos[s];// position de 's' dans le tas
	int posP = posS / 2;
	//printf("val[posP] = %lf val[posS] = %lf posS = %d posP = %d\n", t->val[posP], t->val[posS], posS, posP);
	if (t->val[posP] > t->val[posS] && posS > 1) {
		//printf("\techange %d:%lf avec %d:%lf\n", t->elems[posP], t->val[posP], t->elems[posS], t->val[posS]);
		tas_echanger(t, posS, posP);
		tas_monter(t, s);
	}
}

void tas_descendre(Tas t, int s) {
	int posS = t->pos[s];
	int taille = t->elems[0];
	int posF = posS * 2; // Position du fils gauche (s'il existe)

	//printf("rec descendre s=%d taille=%d\n", s, taille);
	if (posF > taille) { return; } // Pas de fils gauche donc pas de droit non plus

	if (posF + 1 <= taille && t->val[posF + 1] < t->val[posF]) {// On compare le fils droit au gauche s'il existe
		posF++;// On le sélectionne car de valeur inférieur au fils gauche
	}
	//printf("val fils=%lf \t fils=%d\n", t->val[posF], t->elems[posF]);
	if (t->val[posF] < t->val[posS]) {// Le fils est plus "leger" que le père
		//printf("echangeons s1=%d et s2=%d\n", t->elems[posF], t->elems[posS]);
		tas_echanger(t, posF, posS);
		tas_descendre(t, s);// On continue de faire descendre le père
	}
}

void tas_inserer(Tas t, int s, double valeur) {
	int taille = ++t->elems[0];

	t->elems[taille] = s;
	t->val[taille] = valeur;
	t->pos[s] = taille;

	//tas_afficher(t);
	tas_monter(t, s);
}

void tas_update(Tas t, int s, double newValeur) {
	int pos = t->pos[s];
	if(pos==-1){return;}
	double oldValeur = t->val[pos];
	t->val[pos] = newValeur;

	if (oldValeur < newValeur) {
		tas_descendre(t, s);
	} else {
		tas_monter(t, s);
	}
}

void tas_retirer(Tas t, int s) {
	int pos = t->pos[s];
	tas_echanger(t, pos, t->elems[0]);
	t->elems[0]--;
	tas_descendre(t, t->elems[pos]);
	t->pos[s]=-1;
}

int tas_retirer_tete(Tas t) {
	int s = t->elems[1];

	tas_retirer(t, s);

	return s;
}

void tas_afficher(Tas t) {
	printf("Affichage du tas comportant %d / %d elements:\n", t->elems[0], t->maxTaille);
	int pow2 = 1;
	int i;
	for (i = 1; i <= t->elems[0]; i++) {
		printf("%d:%lf\t", t->elems[i], t->val[i]);
		if (i == pow2) {
			printf("\n");
			pow2 = 2 * pow2 + 1;
		}
	}
	printf("\n");
}

int tas_taille(Tas t) {
	return t->elems[0];
}
