#include"union_find.h"

Union_find* uf_init(int nMax){
    Union_find* uf = (Union_find*) malloc(sizeof(Union_find));
    uf->nMax = nMax;
    uf->parent = (size_t*) malloc(nMax*sizeof(size_t));
    size_t i=0;
    for(i=0;i<nMax;i++){
        uf->parent[i]=i;
    }
    return uf;
}

void uf_setmake(Union_find* uf, size_t x){
    uf->parent[x]=x;
}

void uf_union(Union_find* uf, size_t x,size_t y){
    size_t px = uf_find(uf, x), py = uf_find(uf, y);
    for(size_t i=0; i<uf->nMax; i++){
        if(uf_find(uf, i)==py){
            uf->parent[i]=px;
        }
    }
}
size_t uf_find(Union_find* uf, size_t x){
    size_t p = uf->parent[x];
    if(p!=x)
    {
        return uf_find(uf, p);
    }
    return p;
}

void uf_free(Union_find* uf){
    free(uf->parent);
    free(uf);
}

bool uf_cycle(Union_find* uf, size_t x,size_t y){
    if(uf_find(uf, y)==uf_find(uf, x)){
        return true;
    }
    return false;
}


