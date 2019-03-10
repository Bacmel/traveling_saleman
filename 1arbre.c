#include "1arbre.h"
#include "prim.h"
#include "poid_pi.h"

Graphe graph1arbre(Coordonnees c, Sommet s, double **mat_distances) {
	return graph1arbre_pi(c, s, mat_distances, NULL);
}

Graphe graph1arbre_pi(Coordonnees c, Sommet s, double **mat_distances, double pi[]) {
	Graphe graphe = prim_exclu_pi(c, mat_distances, &s, 1, pi);// Construction de l'arbre optimal sur le sous graph excluant uniquement 's'
	Tas tas = creer_tas(c->n);
	Sommet courant; // Sommet en cours d'étude
	int i; // Compteur d'itération

	for (courant = 0; courant < c->n; courant++) {
		if (courant == s) { continue; }
		tas_inserer(tas, courant, omega_pi(mat_distances, pi, courant, s));
	}
	/* Ajout de 2 arêtes optimales pour relier le sommet exclu de l'arbre optimal */
	for (i = 0; i < 2; i++) {
		graphe_ajouter_arete(graphe, s, tas_retirer_tete(tas));
	}
	/* Libération de la mémoire */
	detruire_tas(&tas);

	return graphe;
}