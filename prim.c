#include "prim.h"
#include "poid_pi.h"

Graphe prim_construit(Coordonnees c, double **distances_tab, Tas tas, Graphe graphe, Sommet predecesseurs[], double pi[]) {
	Sommet last = 0; // Dernier sommet sélectionné
	Sommet courant = 0; // Sommet en cours d'étude
	double poid = 0; // Distance entre sommets

	while (tas_taille(tas) != 0) {
		last = tas_retirer_tete(tas);
		graphe_ajouter_arete(graphe, predecesseurs[last], last);
		for (courant = 0; courant < c->n; courant++) {
			if (courant != last) {
				poid = omega_pi(distances_tab, pi, last, courant);
				if (tas->pos[courant] != -1 && poid < tas->val[tas->pos[courant]]) {
					tas_update(tas, courant, poid);
					predecesseurs[courant] = last;
				}
			}
		}
	}
	return graphe;
}

Graphe prim(Coordonnees c, double **distances_mat) {
	return prim_exclu(c, distances_mat, NULL, 0);
}


Graphe prim_exclu(Coordonnees c, double **distances_mat, Sommet exclus[], int tailleExclus) {
	return prim_exclu_pi(c, distances_mat, exclus, tailleExclus, NULL);
}

Graphe prim_exclu_pi(Coordonnees c, double **distances_mat, int exclus[], int tailleExclus, double pi[]) {
	Graphe graphe = creer_graphe(c->n); // Graphe à construire
	Tas tas = creer_tas(c->n); // Tas utilisé pour sélectionner l'arête optimale
	Sommet predecesseurs[c->n]; // Tableau des prédécesseurs pour chaque arc potentiel
	Sommet last = 0; // Dernier sommet sélectionné
	Sommet courant = 0; // Sommet en cours d'étude

	for (last = 0; est_present(exclus, tailleExclus, last); last++) {} // Sélection du sommet de départ qui ne doit pas être exclu
	// On rempli le tas avec tous les sommets qui ne sont pas exclus
	for (courant = 0; courant < c->n; courant++) {
		if (courant != last && !est_present(exclus, tailleExclus, courant)) {
			tas_inserer(tas, courant, omega_pi(distances_mat, pi, last, courant));
		}
		predecesseurs[courant] = last;// Initialisation du prédécesseur au premier sommet
	}
	prim_construit(c, distances_mat, tas, graphe, predecesseurs, pi); // Construction du graphe

	/* Libération de la mémoire */
	detruire_tas(&tas);

	return graphe;
}