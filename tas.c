#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tas.h"

Tas creer_tas(int taille) {
	Tas tas = (Tas) malloc(sizeof(struct tas)); // Tas à initialiser
	int i; // Indice d'itération

	tas->maxTaille = taille;
	tas->elems = (int *) malloc(sizeof(int) * (taille + 1));
	tas->val = (double *) malloc(sizeof(double) * (taille + 1));
	tas->pos = (int *) malloc(sizeof(int) * (taille + 1));
	// Initialisation à -1, cette valeur est impossible pour les sommets, leur position ou leur poid (jusqu'à la question 8)
	for (i = 0; i < taille; i++) {
		tas->elems[i] = -1;
		tas->val[i] = -1;
		tas->pos[i] = -1;
	}
	tas->elems[0] = 0;// Initialement, le tas ne comporte aucun éléments

	return tas;
}

void detruire_tas(Tas *pTas) {
	free((*pTas)->elems);
	free((*pTas)->val);
	free((*pTas)->pos);
	free(*pTas);
	*pTas = NULL;
}

void tas_echanger(Tas t, int pos1, int pos2) {
	#if DEBUG_MODE
	printf("echange pos1 = %d\tpos2 = %d\n", pos1, pos2);
	printf("\tpos1(%d,%lf,%d)\tpos2(%d,%lf,%d)\n",t->elems[pos1],t->val[pos1],t->pos[t->elems[pos1]], t->elems[pos2],t->val[pos2],t->pos[t->elems[pos2]]);
	#endif
	int temp = t->elems[pos1]; // Echange des éléments
	t->elems[pos1] = t->elems[pos2];
	t->elems[pos2] = temp;

	double tempV = t->val[pos1]; // Echange des valeurs
	t->val[pos1] = t->val[pos2];
	t->val[pos2] = tempV;

	t->pos[t->elems[pos1]] = pos1; // Mise a jour des positions
	t->pos[t->elems[pos2]] = pos2;
	#if DEBUG_MODE
	printf("\tpos1(%d,%lf,%d)\tpos2(%d,%lf,%d)\n",t->elems[pos1],t->val[pos1],t->pos[t->elems[pos1]], t->elems[pos2],t->val[pos2],t->pos[t->elems[pos2]]);
	#endif
}

void tas_monter(Tas t, Sommet s) {
	int posS = t->pos[s];// Indice de 's' dans le tas
	int posP = posS / 2;// Indice du parent de 's' dans le tas
	#if DEBUG_MODE
	printf("val[posP] = %lf val[posS] = %lf posS = %d posP = %d\n", t->val[posP], t->val[posS], posS, posP);
	#endif
	if (t->val[posP] > t->val[posS] && posS > 1) {
		#if DEBUG_MODE
		printf("\techange %d:%lf avec %d:%lf\n", t->elems[posP], t->val[posP], t->elems[posS], t->val[posS]);
		#endif
		tas_echanger(t, posS, posP);
		tas_monter(t, s);
	}
}

void tas_descendre(Tas t, Sommet s) {
	int posS = t->pos[s]; // Indice du sommet 's' dans le tas
	int posF = posS * 2; // Indice du fils gauche (s'il existe)
	int taille = t->elems[0]; // Nombre de sommet présent dans le tas

	#if DEBUG_MODE
	printf("rec descendre s=%d taille=%d\n", s, taille);
	#endif
	if (posF > taille) { return; } // Pas de fils gauche donc pas de droit non plus

	if (posF + 1 <= taille && t->val[posF + 1] < t->val[posF]) {// On compare le fils droit au gauche s'il existe
		posF++;// On le sélectionne car il est de valeur inférieur au fils gauche
	}
	#if DEBUG_MODE
	printf("val fils=%lf \t fils=%d\n", t->val[posF], t->elems[posF]);
	#endif
	if (t->val[posF] < t->val[posS]) {// Le fils est plus "leger" que le père
		#if DEBUG_MODE
		printf("echangeons s1=%d et s2=%d\n", t->elems[posF], t->elems[posS]);
		#endif
		tas_echanger(t, posF, posS);
		tas_descendre(t, s);// On continue de faire descendre le père
	}
}

void tas_inserer(Tas t, Sommet s, double valeur) {
	int taille = ++t->elems[0];// Nombre d'éléments dans le tas +1 car on va ajouter 's'

	// Insertion du sommet à la fin du tas
	t->elems[taille] = s;
	t->val[taille] = valeur;
	t->pos[s] = taille;
	#if DEBUG_MODE
	tas_afficher(t);
	#endif
	tas_monter(t, s);
}

void tas_update(Tas t, Sommet s, double newValeur) {
	if (t->pos[s] == -1) { return; }// Si l'élément n'est pas présent

	int pos = t->pos[s]; // Indice du sommet dans le tas
	double oldValeur = t->val[pos]; // Poid précédent du sommet

	t->val[pos] = newValeur;// Mise à jour du poid

	if (oldValeur < newValeur) {
		tas_descendre(t, s); // Si le sommet est 'alourdi' il est potentiellement plus lourd qu'un de ces fils
	} else {
		tas_monter(t, s); // Sinon il est potentiellement plus 'léger' que son père
	}
}

void tas_retirer(Tas t, Sommet s) {
	if (t->pos[s] == -1) { return; }// Si l'élément n'est pas présent

	int pos = t->pos[s]; // Indice de 's' dans le tas
	int taille = t->elems[0];

	tas_echanger(t, pos, t->elems[0]);// Permutation du sommet avec le dernier élément
	// Suppression de l'élément
	t->elems[taille] = -1;
	t->val[taille] = -1;
	t->pos[s] = -1;
	t->elems[0]--;
	tas_descendre(t, t->elems[pos]);// On descend le sommet (d'après le propriété de tournoi, son poid est supérieur à 's'
}

int tas_retirer_tete(Tas t) {
	int s = t->elems[1];

	tas_retirer(t, s);

	return s;
}

void tas_afficher(Tas t) {
	int pow2 = 1; // Valeur de 2^k
	int i; // Indice d'itération

	printf("Affichage du tas comportant %d / %d elements:\n", t->elems[0], t->maxTaille);

	for (i = 1; i <= t->elems[0]; i++) {
		printf("%d:%lf\t", t->elems[i], t->val[i]);
		if (i == pow2) {// On a fini d'afficher une 'génération'
			printf("\n");
			pow2 = 2 * pow2 + 1;
		}
	}
	printf("\n");
}

int tas_taille(Tas t) {
	return t->elems[0];
}
