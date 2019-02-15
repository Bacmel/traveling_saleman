/* Mini-projet ROB3 Algorithmique 2012-13 */

/* pour compiler : gcc projet.c -o projet */
/* pour lancer le programme après compilation : ./projet nom_du_fichier_tsp_sans_extension */
/* exemple : ./projet berlin52 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/***********************************/
/* les types Graphe et Coordonnees */
/***********************************/

/* type struct graphe */
struct graphe {
    int n;              /* nombre de sommets */
    int m;              /* nombre d'aretes */
    struct voisins {
        int d;          /* degre */
        int nbcell;        /* nombre de cellules dans le tableau */
        char est_trie; /* vrai si la liste est deja triee */
        int list[1];    /* liste des voisins, sous forme d'un tableau dynamique */
    } *alist[1];
};

/*type graphe non-oriente */
typedef struct graphe *Graphe;

/* type struct coordonnees */
struct coordonnees {
	int n;		      /* nombre de points */
	char nom[256];	      /* nom de l'instance */
	struct coord {
		float coordx; /* coordonnee sur l'axe x */
		float coordy; /* coordonnee sur l'axe y */
	} *clist[1];
};

/*type coordonnees */
typedef struct coordonnees *Coordonnees;

/*************************************/
/* 	!!!!!!!	ATTENTION !!!!!!     */
/* 	!!!!!!!	ACHTUNG !!!!!!!!     */
/*	!!!!!!!	BE CAREFUL !!!!!     */
/* les sommets sont indices de 0     */
/* n-1 dans Coordonnees et graph     */
/* MAIS ils sont indicés de 1 a n    */
/* dans les differents fichiers	     */
/*************************************/

/**********************************************************************************/
/* les signatures des fonctions et procedures liees aux graphes et aux affichages */
/**********************************************************************************/

/* cree un nouveau graphe avec n sommets numerotes de 0 a n-1 et aucune arete */
Graphe creer_graphe(int n);

/* libere la memoire utilisee par le graphe g*/
void detruire_graphe(Graphe g);

/* ajoute une arete (s1,s2) a un graphe existant */
/* le faire plus d'une fois peut conduire a des resultats imprevisibles */
void graphe_ajouter_arete(Graphe g, int s1, int s2);

/* retourne le nombre de sommets/aretes d'un graphe g*/
int graphe_nb_sommets(Graphe g);
int graphe_nb_aretes(Graphe g);

/* retourne le degre d'un sommet s dans g*/
int graphe_degre(Graphe g, int s);

/* retourne 1 si l'arete (s1,s2) existe dans g, 0 sinon */
int graphe_arete_existe(Graphe g, int s1, int s2);

/* conversion d'un fichier tour nom_tour.tour en un graphe */
Graphe conversion_tour_graphe(char *nom_tour);

/* cree un tableau de n coordonnees numerotees de 0 a n-1 et toutes a (0,0) */
Coordonnees creer_coordonnees(int n,char *nom);

/* libere la memoire utilisee par les coordonnees c*/
void detruire_coordonnees(Coordonnees c);

/* lit une instance dans le fichier nom.tsp, la charge en memoire dans Coordonnees */
/* et cree un fichier nom.gnu pour l'affichage */
Coordonnees lecture_instance(char* nom);

/* affiche une instance apres lecture de l'instance nom.tsp */
/* a partir du fichier nom.gnu qui a ete genere par lecture_instance */
void afficher_instance(char* nom);

/* affiche une tournee nom_tour.tour */
void afficher_tour(Coordonnees c, char* nom_tour);

/* affiche le graphe g */
void afficher_graphe(Coordonnees c, Graphe g);

/***************************************************************************************/
/* les implementations des fonctions et procedures liees aux graphes et aux affichages */
/***************************************************************************************/

/* cree un nouveau graphe avec n sommets numerotes de 0 a n-1 et aucune arete */
Graphe creer_graphe(int n)
{
    Graphe g;
    int i;

    g = malloc(sizeof(struct graphe) + sizeof(struct voisins *) * (n-1));
    assert(g);

    g->n = n;
    g->m = 0;

    for(i = 0; i < n; i++) {
        g->alist[i] = malloc(sizeof(struct voisins));
        assert(g->alist[i]);

        g->alist[i]->d = 0;
        g->alist[i]->nbcell = 1;
        g->alist[i]->est_trie= 1;
    }
    
    return g;
}

/* libere la memoire utilisee par le graphe g */
void detruire_graphe(Graphe g)
{
    int i;

    for(i = 0; i < g->n; i++) free(g->alist[i]);
    free(g);
}

/* ajoute une arete a un graphe existant */
/* le faire plus d'une fois peut conduire a des resultats imprevisibles */
void graphe_ajouter_arete(Graphe g, int s1, int s2)
{
    assert(s1 >= 0);
    assert(s1 < g->n);
    assert(s2 >= 0);
    assert(s2 < g->n);

    /* est-il necessaire d'agrandir la liste de s1 ? */
    while(g->alist[s1]->d >= g->alist[s1]->nbcell) {
        g->alist[s1]->nbcell *= 2;
        g->alist[s1] =
            realloc(g->alist[s1], 
                sizeof(struct voisins) + sizeof(int) * (g->alist[s1]->nbcell - 1));
    }

    /* est-il necessaire d'agrandir la liste de s2 ? */
    while(g->alist[s2]->d >= g->alist[s2]->nbcell) {
        g->alist[s2]->nbcell *= 2;
        g->alist[s2] =
            realloc(g->alist[s2], 
                sizeof(struct voisins) + sizeof(int) * (g->alist[s2]->nbcell - 1));
    }

    /* ajoute le sommet s2 dans la liste d'adjacence de s1 */
    g->alist[s1]->list[g->alist[s1]->d++] = s2;
    g->alist[s1]->est_trie = 0;

    /* ajoute le sommet s1 dans la liste d'adjacence de s2 */
    g->alist[s2]->list[g->alist[s2]->d++] = s1;
    g->alist[s2]->est_trie = 0;

    /* incremente le compteur d'aretes */
    g->m++;
}

/* retourne le nombre de sommets d'un graphe */
int graphe_nb_sommets(Graphe g)
{
    return g->n;
}

/* retourne le nombre d'aretes d'un graphe */
int graphe_nb_aretes(Graphe g)
{
    return g->m;
}

/* retourne le degre d'un sommet s */
int graphe_degre(Graphe g, int s)
{
    assert(s >= 0);
    assert(s < g->n);

    return g->alist[s]->d;
}

/* a partir d'une liste de longueur 10 */
/* on appelle la recherche dichotomique */
#define BSEARCH_THRESHOLD (10)

static int intcmp(const void *a, const void *b)
{
    return *((const int *) a) - *((const int *) b);
}

/* retourne 1 si l'arete (s1,s2) existe, 0 sinon */
int graphe_arete_existe(Graphe g, int s1, int s2)
{
    int i;

    assert(s1 >= 0);
    assert(s1 < g->n);
    assert(s2 >= 0);
    assert(s2 < g->n);

    if(graphe_degre(g,s1) >= BSEARCH_THRESHOLD) {
        /* on s'assure que c'est trie */
        if(! g->alist[s1]->est_trie) {
            qsort(g->alist[s1]->list,g->alist[s1]->d,sizeof(int),intcmp);
        }
        
        /* on appelle la recherche dichotomique */
        return 
            bsearch(&s2,g->alist[s1]->list,g->alist[s1]->d,sizeof(int),intcmp)!= 0;
    } else {
        /* on realise une simple recherche sequentielle */
        for(i = 0; i < g->alist[s1]->d; i++) {
            if(g->alist[s1]->list[i] == s2) return 1;
        }
        /* sinon */
        return 0;
    }
}

/* conversion d'un fichier tour en un graphe */
Graphe conversion_tour_graphe(char *nom_tour)
{
	FILE* fichier_tour = NULL;
	char temp[256];
	int i,j,dimension,sommet1,sommet2;	
	Graphe g;

	char nom_complet_tour[256];	
	
	/* ouverture en lecture du fichier nom_tour.tour */
	/* exemple : berlin52.opt.tour */
	sprintf(nom_complet_tour,"%s.tour",nom_tour);
	fichier_tour = fopen(nom_complet_tour, "r");

	/* on recupere la dimension dans nom_tour.tour */
	/* exemple : on recupere la dimension dans berlin52.opt.tour */
	do	
	{
		fgets(temp,256,fichier_tour);	
	} while (temp[0] != 'D');
	
	i=0;		
	while (temp[i] != ':') i++;
	i=i+2;
	char dim[256];
	j=0;
	while (temp[i] != '\0')
	{
		dim[j]=temp[i];
		i++; j++;
	}
	dim[j]='\0';
	dimension=atoi(dim);

	/* creation d'un graphe vide */
	g = creer_graphe(dimension);

	/* on se place sur la ligne comportant le sommet 1 dans nom_tour.tour */
	/* exemple : ligne comportant le sommet 1 dans berlin52.opt.tour */
	fgets(temp,256,fichier_tour);
	while(temp[0] != '1') 
	{
		fgets(temp,256,fichier_tour);
	}

	/* on parcourt le fichier nom_tour.tour pour generer le graphe g */
	/* exemple : on parcourt berlin52.opt.tour pour generer le graphe g */
	sommet1=1;
	fscanf(fichier_tour,"%d",&sommet2);	
	while (sommet2 != -1)	
	{
		graphe_ajouter_arete(g,sommet1-1,sommet2-1);		
		sommet1=sommet2;
		fscanf(fichier_tour,"%d",&sommet2);	
	}

	/* on genere la derniere arete de la tournee */
	graphe_ajouter_arete(g,sommet1-1,0);
	
	/* fermeture du fichier nom_tour.tour */
	fclose(fichier_tour);

	return g;
}

/* cree un tableau de n coordonnees numerotees de 0 a n-1 et toutes a (0,0) */
/* le parametre "nom" est le nom que l'on veut donner a l'instance */
Coordonnees creer_coordonnees(int n,char *nom)
{
    Coordonnees c;
    int i;

    c = malloc(sizeof(struct coordonnees) + sizeof(struct coord *) * (n-1));
    assert(c);

    c->n = n;
    sprintf(c->nom,"%s",nom);
    
    for(i = 0; i < n; i++) {
        c->clist[i] = malloc(sizeof(struct coord));
        assert(c->clist[i]);

        c->clist[i]->coordx = 0;
        c->clist[i]->coordy = 0;
    }
    
    return c;
}

/* libere la memoire utilisee par les coordonnees c */
void detruire_coordonnees(Coordonnees c)
{
    int i;

    for(i = 0; i < c->n; i++) free(c->clist[i]);
    free(c);
}

/* lit une instance dans le fichier nom.tsp, charge les coordonnees en memoire dans c */
/* et cree un fichier nom.gnu pour l'affichage */
Coordonnees lecture_instance(char* nom)
{
	int i,j,point,dimension;
	float coordx,coordy;
	char temp[256];
	char* plot = "plot";
 	FILE* fichier_tsp = NULL;
	FILE* fichier_dat = NULL;
	FILE* fichier_gnu = NULL;
	Coordonnees c;

	/* ouverture en lecture du fichier nom.tsp */
	/* exemple : berlin52.tsp */
	char nom_tsp[256];
       	sprintf(nom_tsp,"%s.tsp",nom); 
	fichier_tsp = fopen(nom_tsp, "r");

	/* ouverture en ecriture du fichier nom.dat */
	/* le fichier stocke les differents points */
	/* sous un format interpretable par gnuplot */
	/* exemple : berlin52.dat */	
	char nom_dat[256];
	sprintf(nom_dat,"%s.dat",nom); 
	fichier_dat = fopen(nom_dat, "w");
	
	/* ouverture en ecriture du fichier nom.gnu */
	/* le fichier nom.gnu fait appel a nom.dat */
	/* exemple : berlin52.gnu */	
	char nom_gnu[256];
	sprintf(nom_gnu,"%s.gnu",nom); 
	fichier_gnu = fopen(nom_gnu, "w");

	if ((fichier_tsp != NULL)&&(fichier_dat != NULL)&&(fichier_gnu != NULL))
	{
        	/* on recupere la dimension dans nom.tsp */
		/* exemple : on recupere la dimension dans berlin52.tsp */
		for (i=0;i<3;i++) fgets(temp,256,fichier_tsp);
		fgets(temp,256,fichier_tsp);
		i=0;		
		while (temp[i] != ':') i++;
		i=i+2;
		char dim[256];
		j=0;
		while (temp[i] != '\0')
		{
			dim[j]=temp[i];
			i++; j++;
		}
		dim[j]='\0';
		dimension=atoi(dim);

		/* creation du tableau de coordonnees */
		c = creer_coordonnees(dimension,nom);

		/* on charge les coordonnees en memoire a partir du fichier nom.tsp */
		/* exemple : a partir de berlin52.tsp */
		for (i=0;i<2;i++) fgets(temp,256,fichier_tsp);
		for (i=0;i<c->n;i++)
		{
			fscanf(fichier_tsp,"%d %f %f",&point,&coordx,&coordy);	
			c->clist[point-1]->coordx = coordx;
			c->clist[point-1]->coordy = coordy;		
			fprintf(fichier_dat,"%d %f %f \n",point,coordx,coordy);
		}
	}	
    	else	
	{	
	        /* On affiche un message d'erreur */
	        printf("Impossible d'ouvrir le fichier");
	}

	/* on genere les dernieres lignes de berlin52.gnu */
	fprintf(fichier_gnu,"%s",plot);
	fprintf(fichier_gnu,"%c",' ');
        fprintf(fichier_gnu,"%c",putchar(39));
	fprintf(fichier_gnu,"%s",nom_dat);
 	fprintf(fichier_gnu,"%c",putchar(39));
	fprintf(fichier_gnu,"%s"," u 2:3 title ");
	fprintf(fichier_gnu,"%c",putchar(39));
	fprintf(fichier_gnu,"%s",nom);
 	fprintf(fichier_gnu,"%c",putchar(39));
	fprintf(fichier_gnu,"%c",'\n');
	fprintf(fichier_gnu,"%s","pause -1");
	fprintf(fichier_gnu,"%c",'\n');

	/* on ferme les differents fichiers */
	fclose(fichier_tsp);
	fclose(fichier_dat);
	fclose(fichier_gnu);
		
	/* retourne les coordonnees */
	return c;
}

/* affiche une instance apres lecture de l'instance nom.tsp */
/* a partir du fichier nom.gnu qui a ete genere */
void afficher_instance(char* nom)
{
	char commande[256];
       	sprintf(commande,"gnuplot %s.gnu",nom);
	system(commande);	 
}

/* affiche une tournee nom_tour.tour */
/* prerequis : avoir lance lecture_instance au prealable */
/* exemple : affiche berlin52.opt.tour apres avoir lu berlin52.tsp */
void afficher_tour(Coordonnees c, char* nom_tour)
{
	FILE* fichier_gnu = NULL;
	FILE* fichier_tour_gnu = NULL;	
	FILE* fichier_tour = NULL;
	int i,sommet1,sommet2;	

	char nom_gnu[256];
	char nom_tour_gnu[256];	
	char nom_complet_tour[256];	
	
	/* ouverture en lecture du fichier (c->nom).gnu */
	/* exemple : berlin52.gnu */
	sprintf(nom_gnu,"%s.gnu",c->nom);
	fichier_gnu = fopen(nom_gnu, "r");

	/* ouverture en ecriture du fichier nom_tour.gnu */
	/* exemple : berlin52.opt.gnu */
	sprintf(nom_tour_gnu,"%s.gnu",nom_tour);
	fichier_tour_gnu = fopen(nom_tour_gnu, "w");

	/* ouverture en lecture du fichier nom_tour.tour */
	/* exemple : berlin52.opt.tour */
	sprintf(nom_complet_tour,"%s.tour",nom_tour);
	fichier_tour = fopen(nom_complet_tour, "r");

	/* on se place sur la ligne comportant le sommet 1 dans nom_tour.tour */
	/* exemple : ligne comportant le sommet 1 dans berlin52.opt.tour */
	char temp[256];	
	fgets(temp,256,fichier_tour);
	while(temp[0] != '1') 
	{
		fgets(temp,256,fichier_tour);
	}

	/* on copie la premiere ligne de nom.gnu dans nom_tour.gnu */	
	/* exemple : on copie de berlin52.gnu vers berlin52.opt.gnu */
	char ligne[256];	
	fgets(ligne,sizeof(ligne),fichier_gnu);       
	fprintf(fichier_tour_gnu,"%s",ligne);
	
	/* on parcourt le fichier nom_tour.tour pour generer nom_tour.gnu */
	/* exemple : on parcourt berlin52.opt.tour pour generer berlin52.opt.gnu */
	sommet1=1;
	fscanf(fichier_tour,"%d",&sommet2);	
	while (sommet2 != -1)	
	{
		fprintf(fichier_tour_gnu,"set arrow from %f,%f to %f,%f nohead\n",c->clist[sommet1-1]->coordx,c->clist[sommet1-1]->coordy,c->clist[sommet2-1]->coordx,c->clist[sommet2-1]->coordy);
		sommet1=sommet2;
		fscanf(fichier_tour,"%d",&sommet2);	
	}

	/* on genere les dernieres lignes de nom_tour.gnu */
	/* exemple : on genere les dernieres lignes de berlin52.opt.gnu */
	fprintf(fichier_tour_gnu,"set arrow from %f,%f to %f,%f nohead\n",c->clist[sommet1-1]->coordx,c->clist[sommet1-1]->coordy,c->clist[0]->coordx,c->clist[0]->coordy);
	fprintf(fichier_tour_gnu,"%s","replot\n");	
	fprintf(fichier_tour_gnu,"%s","pause -1\n");

	/* fermeture des differents fichiers */
	fclose(fichier_gnu);
	fclose(fichier_tour_gnu);
	fclose(fichier_tour);

	/* affichage obtenu par 'gnuplot nom_tour.gnu' */
	/* exemple : affichage obtenu par 'gnuplot berlin52.opt.gnu' */ 
	char commande[256];
	sprintf(commande,"gnuplot %s.gnu",nom_tour);
	system(commande);
}

/* affiche le graphe g */
/* prerequis : avoir lance lecture_instance au prealable */
void afficher_graphe(Coordonnees c, Graphe g)
{
	FILE* fichier_gnu = NULL;	
	FILE* fichier_graphe_gnu = NULL;
	int i,sommet1,sommet2;	
	char nom_gnu[256];
	
	/* ouverture en lecture de nom.gnu */
	/* exemple : berlin52.gnu */
	/* ouverture en ecriture de "graphe.gnu" */
	sprintf(nom_gnu,"%s.gnu",c->nom);
	fichier_gnu = fopen(nom_gnu, "r");	
	fichier_graphe_gnu = fopen("graphe.gnu", "w");
	
	/* generation de "graphe.gnu" a partir de nom.gnu et de g */
	char ligne[256];	
	fgets(ligne,sizeof(ligne),fichier_gnu);       
	fprintf(fichier_graphe_gnu,"%s",ligne);
	for(sommet1 = 0; sommet1 < g->n; sommet1++) {
		for (i = 0; i < g->alist[sommet1]->d; i++) {
			sommet2 = g->alist[sommet1]->list[i];
			if (sommet2 > sommet1) fprintf(fichier_graphe_gnu,"set arrow from %f,%f to %f,%f nohead\n",c->clist[sommet1]->coordx,c->clist[sommet1]->coordy,c->clist[sommet2]->coordx,c->clist[sommet2]->coordy);		
		}
	}
	fprintf(fichier_graphe_gnu,"%s","replot\n");	
	fprintf(fichier_graphe_gnu,"%s","pause -1\n");

	/*fermeture des differents fichiers */
	fclose(fichier_gnu);
	fclose(fichier_graphe_gnu);

	/* affichage */
	system("gnuplot graphe.gnu");
}

/********/
/* main */
/********/

/* le contenu du fichier main est donne ici a titre de demonstration */
/* du fonctionnement des differentes fonctions et procedures */
int main(int argc, char *argv[])
{
	Graphe g;
	Coordonnees c;

	/* lecture de l'instance */
	c = lecture_instance(argv[1]);

	/* affichage de l'instance */
	afficher_instance(argv[1]);
	
	/* affichage de la tournee optimale */
	char nom_tour[256];
	sprintf(nom_tour,"%s.opt",argv[1]);
	afficher_tour(c,nom_tour);
	g = creer_graphe(c->n);
	
	/* toutes les aretes partant du sommet 0 sont presentes */
	int i,j;    	
	for(i = 0; i < c->n; i++) {
        	for(j = 0; j < c->n; j++) {
            		if((i == 0)&&(i!=j)) graphe_ajouter_arete(g, i, j);
        	}
    	}
	printf("le degre du sommet 0 est : %d\n",graphe_degre(g,0));
	afficher_graphe(c,g);	

	/* conversion d'un fichier tour en un graphe */
	detruire_graphe(g);
	g = conversion_tour_graphe(nom_tour);
	afficher_graphe(c,g);

	/* liberation de la memoire */
	detruire_graphe(g);
	detruire_coordonnees(c);

	return 0;
}

