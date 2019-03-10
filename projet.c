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
#include "1arbre.h"

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
	clock_t start1, start2, start3, start4, end1, end2, end3, end4;
	float seconds;
	c = lecture_instance(argv[1]);
	int choix = 0;
	printf("Choix de la fonction (1- 1arbre, 2- borne inferieur, 3- algorithme glouton, 4- algorithme 2opt, 5- algorithme recuit simule): ");
	scanf("%d",&choix);
	if(choix == 1){
        double **tab = creer_distance_tab(c);
        start1 = clock();
        g = graph1arbre(c, 0, tab);
        end1 = clock();
        seconds = (float)(end1 - start1) / CLOCKS_PER_SEC;
        detruire_distance_tab(&tab, c->n);
	}else if(choix == 2){
        double val;
        printf("Valeur UB %s : ", argv[1]);
        scanf("%lf",&val);
        start2 = clock();
        g = borne_inferieur(c, val);
        end2 = clock();
        seconds = (float)(end2 - start2) / CLOCKS_PER_SEC;
	}else if(choix == 3){
        start3 = clock();
        g = algo(c);
        end3 = clock();
        seconds = (float)(end3 - start3) / CLOCKS_PER_SEC;
	}else if(choix == 4){
        start4 = clock();
        g = algo2opt(c);
        end4 = clock();
        seconds = (float)(end4 - start4) / CLOCKS_PER_SEC;
	}else if(choix == 5){
        start4 = clock();
        g = resim(c);
        end4 = clock();
        seconds = (float)(end4 - start4) / CLOCKS_PER_SEC;
	}
	printf("\ntemps : %lf\n",seconds);
	longueur(c,g);
	afficher_graphe(c,g);

	/* liberation de la memoire */
	detruire_coordonnees(c);
	detruire_graphe(g);
	return 0;
}

