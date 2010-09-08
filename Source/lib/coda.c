//  coda.c  librerie-APA-2010  Created by mic on 08/09/10.

#include "coda.h"
#include<stdlib.h>
#include<stdio.h>


typedef struct item_s * item_t;

struct item_s {
    int     num;
    void *  item;
    item_t  next;
} ;

struct coda_s {
    double z,s,d,f,g;
    item_t testa;
    item_t coda;
};

typedef struct coda_s *coda_t;

coda codaInit(void){
    coda_t c;
    
    c=malloc(sizeof(struct coda_s));
    
    
    
    
    return NULL;
}

void codaPush(coda c, void * el){
    item_t i;
    i=malloc(sizeof(struct item_s));
    c->coda=i->next;
    c=i;
}
void * codaGet(coda c){
    return NULL;
}