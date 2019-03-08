/* Mini-projet ROB3 Algorithmique 2012-13 */

/* pour compiler : gcc projet.c -o projet */
/* pour lancer le programme après compilation : ./projet nom_du_fichier_tsp_sans_extension */
/* exemple : ./projet berlin52 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "graph.h"
#include "tas.h"
#include "prim.h"
#include "utils.h"
#include "poid_pi.h"
#include "glouton.h"
#include "union_find.h"

/********/
/* main */
/********/

/* le contenu du fichier main est donne ici a titre de demonstration */
/* du fonctionnement des differentes fonctions et procedures */
int main(int argc, char *argv[]) {
	srand(time(NULL));
	Graphe g;
	Coordonnees c;

	/* lecture de l'instance */
	c = lecture_instance(argv[1]);
	g = algo(c);
	longueur(c, g);
	afficher_graphe(c,g);
	g = algo2opt(c);
	longueur(c, g);
	afficher_graphe(c, g);
	g = resim(c);
	longueur(c, g);
	//g = borneInferieur(c);
	//g = opt(c);
	/*double pi[c->n];
	for (int i = 0; i < c->n; ++i) {
		pi[i] = 0;
	}
	g = graph1arbre_pi(c, 0, pi, c->n);
	double **tab = creer_distance_tab(c);
	printf("omega = %lf\n", omega_pi_graphe(g,tab,pi));
	printf("t = %lf\n", t(g, tab, pi, 2));
	detruire_distance_tab(&tab,c->n);*/
	//for(int i=0;i<c->n;i++){
	//g = prim_exclu(c, &i, 1);
	//afficher_graphe(c, g);
	//detruire_graphe(g);
	//}
	/* affichage de l'instance */
	//afficher_instance(argv[1]);
	afficher_graphe(c, g);
	/* affichage de la tournee optimale */
	//char nom_tour[256];
	//sprintf(nom_tour,"%s.opt",argv[1]);
	//afficher_tour(c,nom_tour);
	//g = creer_graphe(c->n);
	/* toutes les aretes partant du sommet 0 sont presentes */
	/* Dummy test
	int i,j;
	for(i = 0; i < c->n; i++) {
			for(j = 0; j < c->n; j++) {
					if((i == 0)&&(i!=j)) graphe_ajouter_arete(g, i, j);
			}
		}
	printf("le degre du sommet 0 est : %d\n",graphe_degre(g,0));
	afficher_graphe(c,g);
	*/

	/* conversion d'un fichier tour en un graphe */
	/*detruire_graphe(g);
	g = conversion_tour_graphe(nom_tour);
	afficher_graphe(c,g);*/

	/* liberation de la memoire */
	detruire_coordonnees(c);
	detruire_graphe(g);
	return 0;
}

