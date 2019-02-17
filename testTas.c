#include "tas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int testInsererRetirer() {
	srand(time(NULL));
	int m = 10;
	int n = 100;
	int maxVal = 10;
	int j;
	double vals[n];
	int i;

	for (j = 0; j < m; j++) {
		Tas t = creer_tas(n);
		for (i = 0; i < n; i++) {
			vals[i] = (double) (rand() % (n * 100)) / 100;

			//printf("Insere %d : %lf\n", i, vals[i]);
			tas_inserer(t, i, vals[i]);
		}
		//tas_afficher(t);
		//printf("\n");
		int s;
		int lastS = -1;
		int ord = 1;
		while (tas_taille(t) != 0 && ord) {
			s = tas_retirer_tete(t);
			//tas_afficher(t);
			//printf("%d:%lf, ", s, vals[s]);
			if (lastS != -1) {
				ord = vals[s] >= vals[lastS] && ord;
			}
			lastS = s;
			//printf("-------\n");
		}
		//printf("\n");
		//printf("Ordonné ? %d\n", ord);

		detruire_tas(&t);
		if(!ord){
			printf("Non trié!");
			return 1;
		}
	}
	return 0;
}
int testUpdate(){
	srand(time(NULL));
	int m = 1;
	int n = 10;
	int maxVal = 10;
	int j;
	double vals[n];
	int i;

	for (j = 0; j < m; j++) {
		Tas t = creer_tas(n);
		for (i = 0; i < n; i++) {
			vals[i] = (double) (rand() % (n * 100)) / 100;

			//printf("Insere %d : %lf\n", i, vals[i]);
			tas_inserer(t, i, vals[i]);
		}
		tas_afficher(t);
		//printf("\n");
		int sRand = rand() % n;
		vals[sRand] = maxVal;
		printf("Update s=%d vers val=%lf\n",sRand,vals[sRand]);
		tas_update(t,sRand,vals[sRand]);
		tas_afficher(t);
		detruire_tas(&t);
	}
	return 0;
}
int main(){
	testUpdate();
	return 0;
}