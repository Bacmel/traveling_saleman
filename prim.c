#include"prim.h"

Graphe prim(Coordonnees c){
    Graphe g = creer_graphe(c->n);
    Tas t =creer_tas(c->n);
    int p[c->n];
    size_t i = 0, k = 0;
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

Graphe prim_exclu(Coordonnees c, int* tab, int n){
    Graphe g = creer_graphe(c->n);
    Tas t =creer_tas(c->n);
    int p[c->n];
    size_t i = 0, k=0;
    double d = 0;
    for(k=0;est_present(tab, n, k);k++){}
    for( i=0; i<c->n;i++){
        if(i!=k && !est_present(tab, n, i)){
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
