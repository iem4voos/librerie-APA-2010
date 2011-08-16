//  coda.c  librerie-APA-2010   Created by mic on 08/09/10.

#include "coda.h"
#include<stdlib.h>
#include<stdio.h>

enum boolean {
    TRUE = 1,
    FALSE = 0
    };

/*---------------FYPEDEF-----------------*/
typedef struct item_s * item_t;
typedef struct item_s item;
typedef struct coda_s coda_t;

/*----------------STRUTTURE---------------*/
struct item_s {
    int     num;
    void *  item;
    item *  next;
    item *  prev; 
} ;

struct coda_s {
    double z,s,d,f,g;
    int nElem;
    item * testa;
    item * coda;
    enum boolean isNumeric;
};

/*-----------------FUNZIONI---------------*/
int codaCount(coda C){
    return C->nElem;
}

void codaPush(coda C, void * elemento){
    struct item_s *I;
    I = malloc(sizeof(struct item_s));
    I->item=elemento;
    I->prev = NULL;
    I->next = C->testa;
    
    if (C->nElem ==0 ) {
        C->coda= I;
    }else{
        C->testa->prev=I;
    }
    C->testa = I;
    C->nElem ++;
}

void codaPushNum(coda C, float num){
    float *f;
    f = malloc(sizeof(float));
    *f=num;
    codaPush(C, f);
}

coda codaInit(void){
    coda_t *c;
    c=malloc(sizeof(struct coda_s));
    c->coda=c->testa=NULL;
    c->nElem=0;
    c->isNumeric = FALSE;
    return c;
}

coda codaInitNumeric(void){
    coda_t *c;
    c= codaInit();
    c->isNumeric = TRUE;
    return c;
}

void codaFree(coda C){
    struct item_s * tmp;
    for (struct item_s * i=C->testa; i!=NULL; ) {
        free(i->item);
        tmp=i;
        i=i->next;
        free(tmp);
    }
}

int codaIsEmpty(coda C){
    if (codaCount(C)==0)
        return 1;
    else
        return 0;
}

/*
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
 */

#define mySmallMacro(cosa,capo,direzione) { \
i = #cosa->#capo->item; \
#cosa->#capo=#cosa->#capo->#direzione; \
#cosa->nElem--;  \
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

float codaGetNum(coda c){
    float * f, num;
    f= codaGet(c);
    num=*f;
    free(f);
    return num;
}

void * codaPop(coda C){
    item *i;
    
    if(C->nElem==0){
        if(DEBUG) puts("coda vuota");
        return NULL;
    }
    i = C->coda->item;
    C->coda=C->coda->prev;
    C->nElem--;
    return i;
}

float codaPopNum(coda C){
    float * f, num;
    f= codaPop(C);
    num=*f;
    free(f);
    return num;
    
}
























