#include "utils.h"
#include <math.h>
#include "prim.h"

double distance(Coordonnees c, int s1, int s2) {
	struct coord *s1Coord = c->clist[s1];
	struct coord *s2Coord = c->clist[s2];
	return sqrt(pow(s1Coord->coordx - s2Coord->coordx, 2) + pow(s1Coord->coordy - s2Coord->coordy, 2));
}

bool est_present(int *tab, int n, int i) {
	int j;
	for (j = 0; j < n; j++) {
		if (tab[j] == i) {
			return true;
		}
	}
	return false;
}

Graphe graph1arbre(Coordonnees c, int s) {
	Graphe g = prim_exclu(c, &s, 1);// Construction de l'arbre optimal sur le sous graph excluant uniquement 's'
	Tas t = creer_tas(c->n);
	int i;

	for (i = 0; i < c->n; i++) {
		if (i == s) { continue; }// On ignore le sommet hors de l'arbre
		tas_inserer(t, i, distance(c, i, s));
	}

	for (i = 0; i < 2; i++) {
		graphe_ajouter_arete(g, s, tas_retirer_tete(t)); // Ajout des 2 arretes de valeurs minimales
	}

	detruire_tas(&t);
	return g;
}

double score(Coordonnees c, double pi[], int s1, int s2) {
	return pi[s1] + pi[s2] + distance(c, s1, s2);
}

Graphe graph1arbre_pi(Coordonnees c, int s, double pi[], int taillePi) {
	Graphe graphe = prim_exclu_pi(c, pi, taillePi, &s, 1);
	Tas tas = creer_tas(c->n);
	int s_i;
	int i;

	for (s_i = 0; s_i < c->n; s_i++) {
		if (s_i == s) { continue; }
		tas_inserer(tas, s_i, score(c, pi, s_i, s));
	}

	for (i = 0; i < 2; i++) {
		graphe_ajouter_arete(graphe, s, tas_retirer_tete(tas));
	}

	detruire_tas(&tas);
	return graphe;
}

void a_remove(int *tab, int n, int s){
    int hasRemove = 0;
    int i;

    for(i = 0; i < n-1 ; i++){
        if(tab[i] == s){
            hasRemove = 1;
        }
        if(hasRemove) {
            tab[i] = tab[i + 1];
        }
    }
}

void graphe_supprimer_arete(Graphe g, int s1, int s2){
    if(!graphe_arete_existe(g, s1, s2)) { return; }

    a_remove(g->alist[s1]->list, g->alist[s1]->d, s2);
    g->alist[s1]->d--;
    a_remove(g->alist[s2]->list, g->alist[s2]->d, s1);
    g->alist[s2]->d--;
}
