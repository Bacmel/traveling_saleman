#include"prim.h"

Graphe* prim(Tas* t){
    Graphe* g = (Graphe*)creer_graphe(tas_taille(t));
    int i;
    while(tas_taille(t)){
        i = tas_retirer_tete(t);
    }
    return *g;
}
