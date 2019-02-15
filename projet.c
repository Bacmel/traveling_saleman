/* Mini-projet ROB3 Algorithmique 2012-13 */

/* pour compiler : gcc projet.c -o projet */
/* pour lancer le programme après compilation : ./projet nom_du_fichier_tsp_sans_extension */
/* exemple : ./projet berlin52 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "tas.h"

/********/
/* main */
/********/

/* le contenu du fichier main est donne ici a titre de demonstration */
/* du fonctionnement des differentes fonctions et procedures */
int main(int argc, char *argv[])
{
	Graphe g;
	Coordonnees c;
	Tas t;

	/* lecture de l'instance */
	c = lecture_instance(argv[1]);

	/* affichage de l'instance */
	//afficher_instance(argv[1]);
	
	/* affichage de la tournee optimale */
	//char nom_tour[256];
	//sprintf(nom_tour,"%s.opt",argv[1]);
	//afficher_tour(c,nom_tour);
	g = creer_graphe(c->n);
	t = creer_tas(c->n);
	
	int i;
	for(i = 0; i < 5; i++) {
		tas_inserer(t, i, c);
		tas_afficher(t);
	}
	printf("tete : %d\n", tas_retirer_tete(t));
	tas_afficher(t);
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
	detruire_graphe(g);
	detruire_coordonnees(c);
	detruire_tas(&t);
	
	return 0;
}

