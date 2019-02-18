#include"prim.h"

Graphe prim(Coordonnees c){
    Graphe g = creer_graphe(c->n);
    Tas t =creer_tas(c->n);
    int p[c->n];
    size_t i = 0, k = rand()%c->n;
    double d = 0;
    for( i=0; i<c->n;i++){
        if(i!=k){
            tas_inserer(t, i, distance(c, k, i));
        }
        p[i]=k;
    }
    while(tas_taille(t)!=0){
        k = tas_retirer_tete(t);
        graphe_ajouter_arete(g, p[k], k);
        for( i=0; i<c->n;i++){
            if(i!=k){
                d = distance(c, k, i);
                if(t->pos[i]!=-1 && d<t->val[t->pos[i]]){
                    tas_update(t, i, d);
                    p[i]=k;
                }
            }
        }
    }
    detruire_tas(&t);
    return g;
}
