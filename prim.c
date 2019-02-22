#include"prim.h"

Graphe prim(Coordonnees c) {
	Graphe g = creer_graphe(c->n);
	Tas t = creer_tas(c->n);
	int p[c->n];
	int i = 0, k = 0;
	double d = 0;
	for (i = 0; i < c->n; i++) {
		if (i != k) {
			tas_inserer(t, i, distance(c, k, i));
		}
		p[i] = k;
	}
	while (tas_taille(t) != 0) {
		k = tas_retirer_tete(t);
		graphe_ajouter_arete(g, p[k], k);
		for (i = 0; i < c->n; i++) {
			if (i != k) {
				d = distance(c, k, i);
				if (t->pos[i] != -1 && d < t->val[t->pos[i]]) {
					tas_update(t, i, d);
					p[i] = k;
				}
			}
		}
	}
	detruire_tas(&t);
	return g;
}

Graphe prim_exclu(Coordonnees c, int *tab, int n) {
	Graphe g = creer_graphe(c->n);
	Tas t = creer_tas(c->n);
	int p[c->n];
	int i = 0, k;
	double d = 0;

	for (k = 0; est_present(tab, n, k); k++) {}

	for (i = 0; i < c->n; i++) {
		if (i != k && !est_present(tab, n, i)) {
			tas_inserer(t, i, distance(c, k, i));
		}
		p[i] = k;
	}
	while (tas_taille(t) != 0) {
		k = tas_retirer_tete(t);
		graphe_ajouter_arete(g, p[k], k);
		for (i = 0; i < c->n; i++) {
			if (i != k) {
				d = distance(c, k, i);
				if (t->pos[i] != -1 && d < t->val[t->pos[i]]) {
					tas_update(t, i, d);
					p[i] = k;
				}
			}
		}
	}
	detruire_tas(&t);
	return g;
}

Graphe prim_exclu_pi(Coordonnees c, double pi[], int taillePi, int exclus[], int tailleExclus) {
	Graphe graphe = creer_graphe(c->n);
	Tas tas = creer_tas(c->n);
	int parent[c->n];
	int s = 0;
	int s_i = 0;
	double scoreS_i = 0;

	for (s = 0; est_present(exclus, tailleExclus, s); s++) {}

	for (s_i = 0; s_i < c->n; s_i++) {
		if (s_i != s && !est_present(exclus, tailleExclus, s_i)) {
			tas_inserer(tas, s_i, score(c, pi, s, s_i));
		}
		parent[s_i] = s;
	}

	while (tas_taille(tas) != 0) {
		s = tas_retirer_tete(tas);
		graphe_ajouter_arete(graphe, parent[s], s);
		for (s_i = 0; s_i < c->n; s_i++) {
			if (s_i != s) {
				scoreS_i = score(c, pi, s_i, s);
				if (tas->pos[s_i] != -1 && scoreS_i < tas->val[tas->pos[s_i]]) {
					tas_update(tas, s_i, scoreS_i);
					parent[s_i] = s;
				}
			}
		}
	}

	detruire_tas(&tas);
	return graphe;
}
