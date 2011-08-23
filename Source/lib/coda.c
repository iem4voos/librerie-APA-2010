//  coda.c  librerie-APA-2010   Created by mic on 08/09/10.

#include "coda.h"

enum boolean {
    TRUE = 1,
    FALSE = 0
    };

enum iteration_status{
    OK, F_STOP, B_STOP
};

//LONG_MAX

/*---------------FYPEDEF-----------------*/
typedef struct item_s * item_t;
typedef struct item_s item;
typedef struct coda_s coda_t;

/*----------------STRUTTURE---------------*/
struct iterator_s{
    item * current;
    coda Coda;
    enum iteration_status status;
};

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
#pragma mark - iterator
coda_iterator codaIteratorInit ( coda C, void * element, enum iteration_direction direction)
{    
    coda_iterator I;
    I=malloc(sizeof(struct iterator_s));
    if (element == NULL) 
    {
        if (direction == FORWARD_ITERATION)
            I->current= C->testa;
        else
            I->current= C->coda;
    }else{
        // need more testiong
        struct item_s * pt;
        for (pt=C->testa; pt->item!=element || pt!=C->coda; pt=pt->next) ;
        I->current=pt;
    }
    I->Coda=C;
    
    if (I->current == C->testa) I->status = B_STOP;
    if (I->current == C->coda)  I->status = F_STOP;
    return I;
}

void codaIteratorFree(coda_iterator I){
    free(I);
}

void * coda_Next(coda_iterator I){
    item_t pt;
    // se e arrivato alla fine e sussistono errori rituena null
    if ( I==NULL || (pt = I->current) == NULL || I->status == F_STOP  )
        return NULL;
    // se e arrivato alll ultimo si ferma e le prissime chiamate risponde null
    if ( pt->next == NULL) {
        I->status=F_STOP;
    }else{
        I->status=OK;
        I->current=pt->next;
    }
    return pt->item;
}

void * coda_Prev(coda_iterator I){
    item_t pt;
     // se e arrivato alla fine e sussistono errori rituena null
    if ( I==NULL || (pt = I->current) == NULL || I->status==B_STOP )
        return NULL;
    // se e arrivato alll ultimo si ferma e le prissime chiamate risponde null
    if ( pt->prev== NULL) {
        I->status=B_STOP;
    }else{
        I->status=OK;
        I->current=pt->prev;
    }
    return pt->item;
}

#pragma mark numeric
float coda_NextNum(coda_iterator I){
    float * f, num;
    f=coda_Next(I);
    if (f==NULL) 
        return CODA_ITERATION_END;
    num=*f;
    return num;
}

float coda_PrevNum(coda_iterator I){
    float * f, num;
    f=coda_Prev(I);
    if (f==NULL) 
        return CODA_ITERATION_END;
    num=*f;
    return num;
}

#pragma mark - generic

int codaCount(coda C){
    return C->nElem;
}

coda codaInit(void){
    coda_t *c;
    c=malloc(sizeof(struct coda_s));
    c->coda=c->testa=NULL;
    c->nElem=0;
    c->isNumeric = FALSE;
    return c;
}

void codaFree(coda C){
    struct item_s * tmp;
    for (struct item_s * i=C->testa; i!=NULL;   ) {
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

#pragma mark - pop/get

void codaPushUnique(coda C, void * elemento, int (*funcPtCompare)(void *, void *)){
    coda_iterator I;
    void *x;
    I=codaIteratorInit(C, NULL, FORWARD_ITERATION);
    
    while ( (x=coda_Next(I)) ) {
        if ( funcPtCompare(x, elemento) == 0 ) {
            return;
        }
    }
    
    if (x==NULL) {
        codaPush(C, elemento);
    }
    
    codaIteratorFree(I);
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

#pragma mark - Numeric

coda codaInitNumeric(void){
    coda_t *c;
    c= codaInit();
    c->isNumeric = TRUE;
    return c;
}

void codaPushNum(coda C, float num){
    float *f;
    f = malloc(sizeof(float));
    *f=num;
    codaPush(C, f);
}

float codaGetNum(coda c){
    float * f, num;
    f= codaGet(c);
    num=*f;
    free(f);
    return num;
}

float codaPopNum(coda C){
    float * f, num;
    f= codaPop(C);
    if (f==NULL) {
        return -1;
    }
    num=*f;
    free(f);
    return num;
    
}

#pragma mark - test

void coda_selfTest1(void){
    coda C;
    coda_iterator I;
    float x;
    
    C = codaInitNumeric();
    for (int i=0; i<5; i++) {
        codaPushNum(C, i);
    }
    
    puts("Iteratore avanti");
    I=codaIteratorInit(C, NULL, FORWARD_ITERATION);
    
    while ((x=coda_NextNum(I))!=CODA_ITERATION_END) {
        printf(">%d\n",(int)x);
    }
    puts("Iteratore indietro");
    
    while ((x=coda_PrevNum(I))!=CODA_ITERATION_END) {
        printf(">%d\n",(int)x);
    }
    
    puts("svuoto la coda");
    for (int i=0; !codaIsEmpty(C); i++) {
        printf("%d\n", (int)codaGetNum(C) );
        //printf("%d\n", (int)codaPopNum(C) );
    }

    codaIteratorFree(I);
    codaFree(C);
    
    return;
}

//void codaDelSelected(coda C, void * elemento)

#warning "da fare o almeno cotrollare"
/*

void * codaDelByElement(coda C , void * elemento){
    
    struct item_s * tmp;
    void *pt;
    
    if (C->testa->item == elemento) {
        C->testa=C->testa->next;
        C->testa->prev=NULL;
    }
    
    if (C->coda->item == elemento) {
        C->coda=C->testa->prev;
        C->testa->next=NULL;
    }
    
    for (tmp=C->testa->next;
         tmp->next != C->coda && tmp->item!=elemento;
         tmp=tmp->next); 
    
    if (tmp->item==elemento) {
        tmp->next->prev=tmp->prev;
        tmp->prev->next=tmp->next;
        C->nElem--;
        pt=tmp->item;
        free(tmp);
        puts("coda: rimosso elemento");
        return pt;
    }
    puts("coda: elemento non trovato per rimoxione");
    return NULL;
}
*/

/* return NULL se non trova elemento
 *  contronta tutti gli elementi della lista usando la funzione compare e l'elemento
 */

void * codaDelByCompare(coda C, void * elemento, int (*funcPtCompare)(void *, void *)){

    struct item_s * x;
    void * the_item;
    
    //scorre la lista, se trova un elemento uguale si ferma con in X memorizzato l'elemento corrente
    for (x=C->testa; x!=NULL; x=x->next) {
        if (funcPtCompare(x->item, elemento) ==0 ) {
            break;
        }
    }
    
    if (x==C->testa) {
        C->testa = x->next;
        x->next->prev=NULL;
    }else if(x== C->coda ){
        C->coda=x->prev;
        x->prev->next=NULL;
    }else if(x==NULL){
        return NULL;         //can exit in another point
    }else{
    // the element is in middle
        x->next->prev=x->prev;
        x->prev->next=x->next;
    }
    
    the_item= x->item;
    free(x);
    return the_item;
}





















