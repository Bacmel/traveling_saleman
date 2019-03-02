#include"glouton.h"

Arete* creation_arete(Coordonnees c){
    Arete* a = (Arete*)malloc(((c->n-1)*c->n)/2*sizeof(Arete));
    size_t k=0, i=0, j=0;
    for(i=0;i<c->n-1;i++){
        for(j=i+1;j<c->n;j++){
            a[k].s1 = i;
            a[k].s2 = j;
            a[k].dist = distance(c, i, j);
            k++;

        }
    }
    return a;
}

void fusion(Arete* a, Arete* a1, int n1, Arete* a2, int n2){
    size_t k=0, i=0, j=0;
    while(i<n1 && j<n2){
        if(a1[i].dist<+a2[j].dist){
            a[k]=a1[i];
            i++;
        }
        else{
            a[k]=a2[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        a[k]=a1[i];
        i++;
        k++;
    }
    while(j<n2){
        a[k]=a2[j];
        j++;
        k++;
    }
}

Arete* tri_fusion_arete(Arete* a, int n){
    if(n>1){
        Arete* a1 = (Arete*) malloc((n/2)*sizeof(Arete));
        Arete* a2 = (Arete*) malloc(((n+1)/2)*sizeof(Arete));
        size_t k = 0;
        for(k=0;k<n;k++){
            if(k<n/2){
                a1[k]=a[k];
            }
            else{
                a2[k-n/2]=a[k];
            }
        }
        fusion( a, tri_fusion_arete(a1, n/2), n/2, tri_fusion_arete(a2, ((n+1)/2)), (n+1)/2);
        free(a1);
        free(a2);
    }
    return a;
}

void detruire_arete(Arete* a){
    free(a);
}

Graphe algo(Coordonnees c){
    Graphe g = creer_graphe(c->n);
    Union_find* u = uf_init(c->n);
    Arete* a = creation_arete(c);
    a = tri_fusion_arete(a, ((c->n-1)*c->n)/2);
    size_t t=0, s1, s2;
    for(t=0;graphe_nb_aretes(g)< c->n-1;t++){
        s1 = a[t].s1;
        s2 = a[t].s2;
        if(graphe_degre(g, s1)<2 && graphe_degre(g, s2)<2 && !uf_cycle(u, s1, s2)){
            graphe_ajouter_arete(g, s1, s2);
            uf_union(u, s1, s2);
        }
    }
    s1=0, s2=0;
    while(graphe_degre(g, s1)==2){
        s1++;
    }
    s2=s1+1;
    while(graphe_degre(g, s2)==2){
        s2++;
    }
    graphe_ajouter_arete(g, s1, s2);
    detruire_arete(a);
    uf_free(u);
    return g;
}
