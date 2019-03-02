#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#ifndef UNION_FIND_H
#define UNION_FIND_H
typedef struct union_find{
int nMax;
size_t* parent;
} Union_find;

Union_find* uf_init(int nMax);
void uf_setmake(Union_find* uf, size_t x);
void uf_union(Union_find* uf, size_t x,size_t y);
size_t uf_find(Union_find* uf, size_t x);
void uf_free(Union_find* uf);
bool uf_cycle(Union_find* uf, size_t x,size_t y);
#endif
