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

Hamiltonien* creation_hamiltonien(Graphe g){
    Hamiltonien* H = (Hamiltonien*) malloc(sizeof(Hamiltonien));
    H->n = g->n;
    H->pred = (size_t*)malloc(H->n*sizeof(size_t));
    H->succ = (size_t*)malloc(H->n*sizeof(size_t));
    size_t t = 0, P_i = 0, ind_i = 0;
    for(size_t i=0;t<H->n;i=H->succ[i])
    {
        if(g->alist[i]->list[ind_i]==P_i){
            if(ind_i==1){
                ind_i=0;
            }
            else{
                ind_i=1;
            }
        }
        H->succ[i]=g->alist[i]->list[ind_i];
        H->pred[H->succ[i]]=i;
        P_i=i;
        t++;
    }
    return H;
}

void change_hamiltonien(Hamiltonien* H, size_t i, size_t i2, size_t j, size_t j2){
    H->succ[i]=j;
    H->succ[j]=H->pred[j];
    H->pred[j]=i;
    H->pred[i2]=H->succ[i2];
    H->succ[i2]=j2;
    H->pred[j2]=i2;
    size_t k = 0, temp;
    for(k=H->succ[j]; k!=i2 ; k=H->succ[k])
    {
        temp = H->succ[k];
        H->succ[k] = H->pred[k];
        H->pred[k] = temp;
    }
}
void detruire_hamiltonien(Hamiltonien* H){
    free(H->succ);
    free(H->pred);
    free(H);
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

Graphe algo2opt(Coordonnees c){
    Graphe g = algo(c);
    Hamiltonien* H = creation_hamiltonien(g);
    bool amelioration = true;
    while(amelioration){
        amelioration = false;
        size_t t=0, i=0, j=0;
        for(i=0; t<g->n; i=H->succ[i]){
            for(j=H->succ[i];j!=i;j=H->succ[j]){
                if(j!=i && j!=H->succ[i] && j!=H->pred[i]){
                    if(distance(c, i, H->succ[i]) + distance(c, j, H->succ[j])>distance(c, i, j) + distance(c, H->succ[i], H->succ[j]))
                    {
                        graphe_supprimer_arete(g, i, H->succ[i]);
                        graphe_supprimer_arete(g, j, H->succ[j]);
                        graphe_ajouter_arete(g, i, j);
                        graphe_ajouter_arete(g, H->succ[i], H->succ[j]);
                        change_hamiltonien(H, i, H->succ[i], j, H->succ[j]);
                        amelioration = true;
                    }
                }
            }
            t++;
        }
    }
    detruire_hamiltonien(H);
    return g;
}

Graphe resim(Coordonnees c){
    Graphe g = algo(c);
    Hamiltonien* H = creation_hamiltonien(g);
}
