//  coda.c  librerie-APA-2010  Created by mic on 08/09/10.

#include "coda.h"
#include<stdlib.h>
#include<stdio.h>

/*---------------FYPEDEF-----------------*/
typedef struct item_s * item_t;
typedef struct item_s item;
typedef struct coda_s coda_t;

/*----------------STRUTTURE---------------*/
struct item_s {
    int     num;
    void *  item;
    item *  next;
} ;

struct coda_s {
    double z,s,d,f,g;
    int nElem;
    item * testa;
    item * coda;
};

/*-----------------FUNZIONI---------------*/
coda codaInit(void){
    coda_t *c;
    c=malloc(sizeof(struct coda_s));
    c->coda=c->testa=NULL;
    c->nElem=0;
    return c;
}

void codaAppend(coda c, void * el){
    item * i;
    
    i=malloc(sizeof(item));
    i->item=el;
    
    if(c->nElem==0){
        c->testa=c->coda=i;
        c->nElem=1;
        if(DEBUG) puts("aggiunto primo elemento");
    }else{
        c->coda->next=i;
        c->coda=i;
        c->nElem++;
        if(DEBUG) puts("aggiunto n-esimo elemento");
    }
}
void * codaGet(coda c){
    item *i;
    
    if(c->nElem==0){
        if(DEBUG) puts("coda vuota");
        return NULL;
    }
        
    i=c->testa->item;
    c->testa=c->testa->next;
    c->nElem--;
    return i;
}






















