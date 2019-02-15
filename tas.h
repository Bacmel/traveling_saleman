#ifndef TAS_H
#define TAS_H

struct tas {
	int * elems; // Liste des sites
	double * val; // Distance (valeur)
	int * pos; // Position du site dans le tas
};
#endif
