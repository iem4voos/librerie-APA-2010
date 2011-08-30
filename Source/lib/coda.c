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
    int nElem;
    item * testa;
    item * coda;
    enum boolean isNumeric;
};

/*-------protopipi locali-------*/
int compare_float(void *, void *);


/*-----------------FUNZIONI---------------*/
#pragma mark - iterator

/* L'iteratore va inizializzzato sulla coda subito prima del luo uso perche non tiene conto dei eventi occorsi prima o dopo la sua inizializzazione
 
    per essere precisi non tiene conto dei elementi aggiunti in testa dopo l'inizializzazione nel caso del FORWARD e aggiunti in coda se BACKWARD
 */
coda_iterator codaIteratorInit ( coda C, void * element, enum iteration_direction direction)
{    
    coda_iterator I;
    I=malloc(sizeof(struct iterator_s));
    I->Coda=C;
    
    if (element == NULL){
        codaIteratorRewindFor(I,direction);
    }else{
        // need more testiong
        struct item_s * pt;
        for (pt=C->testa; pt->item!=element || pt!=C->coda; pt=pt->next) ;
        I->current=pt;
    }
    
    I->status = OK;
    return I;
}

void codaIteratorRewindFor(coda_iterator I,enum iteration_direction direction )
{    
    if (direction == FORWARD_ITERATION)
        I->current= I->Coda->testa;
    else
        I->current= I->Coda->coda;
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
    if (C==0) 
        return 0;
    
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
    struct item_s *i;
    
    i = malloc(sizeof(struct item_s));
    i->item=elemento;
    i->prev = NULL;
    
    i->next = C->testa; // perche si mette lui in testA, se e vuota la testa e null
    
    if (C->nElem ==0 ) {  // questo e il primo elento
        C->coda= i;
    }else{
        i->next->prev=i;
    }
    C->testa = i;
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

/*  return NULL se non trova elemento
 *  contronta tutti gli elementi della lista usando la funzione compare
 *
 *   coda C, - coda nella quale controlle e estrae
 *   void * elemento  elemento che viene passato a "compare"
 *  comapre () must return 0 if equal 1 if diversi;
 */

void * codaDelByCompare(coda C, void * elemento, int (*funcPtCompare)(void *, void *))
{
    struct item_s * x;
    void * the_item_content;
    
    for (x=C->testa; x!=NULL && funcPtCompare(x->item, elemento) !=0 ; x=x->next) ;
    
     puts("coda: rimozione elemento da....");
    
    if (x==C->testa) {  // element on top
        if(C->testa!=C->coda){
            C->testa = x->next;
            x->next->prev=NULL;
        }else{
            C->testa=C->coda=NULL;
        }
        puts("testa");
    }else if(x== C->coda ){     // element on bottom
        C->coda=x->prev;
        x->prev->next=NULL;
        puts("coda");
    }else if(x==NULL){          // NO element Found
        puts("oltre la fine");
        return NULL;        //..can exit in another point! pointers must exist
    }else{                      // the element is in middle
        x->next->prev=x->prev;
        x->prev->next=x->next;
        puts("middle");
    }
    
    the_item_content= x->item;
    free(x);
    C->nElem--;
    return the_item_content;
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

int compare_float(void *a, void *b){
    if ( *(float *)a == *(float *)b)
        return 0;
    else
        return 1;
}

/*  On error or not found return CODA_FLOAT_ERROR
 *  works on numeric coda codaInitNumeric(void);
*/
float codaDelNum(coda C, float num){
    float *f,x;
    f= codaDelByCompare(C, &num, compare_float);
    
    if (f==NULL) {
        if(DEBUG)printf("the numer not exist");
        return CODA_FLOAT_ERROR ;
    }
    x=*f;
    printf("canecellato %.2f",x);
    return x;
}

#pragma mark - test

void coda_selfTest1(void){
    coda C;
    coda_iterator I;
    float x;
    
    C = codaInitNumeric();
    
    codaPushNum(C, 99);
    
    puts("Iteratore avanti");
    I=codaIteratorInit(C, NULL, FORWARD_ITERATION);
    while ((x=coda_NextNum(I))!=CODA_ITERATION_END)
        printf(">%d\n",(int)x);
    
    for (int i=0; i<5; i++)
        codaPushNum(C, i);
    
    puts("Iteratore avanti");
    I=codaIteratorInit(C, NULL, FORWARD_ITERATION);
    while ((x=coda_NextNum(I))!=CODA_ITERATION_END)
        printf(">%d\n",(int)x);
    
    float *f, kk=4.0;
    f=&kk;
    
    codaDelByCompare(C, &kk, compare_float);
    
    puts("Iteratore indietro");
    
    while ((x=coda_PrevNum(I))!=CODA_ITERATION_END) {
        printf(">%d\n",(int)x);
    }
    
    codaDelNum(C, 3);
    codaDelNum(C, 2);
    codaDelNum(C, 1);
    codaDelNum(C, 0);
    
    puts("\nsvuoto la coda");
    for (int i=0; !codaIsEmpty(C); i++) {
        printf("%d\n", (int)codaGetNum(C) );
        //printf("%d\n", (int)codaPopNum(C) );
    }

    codaIteratorFree(I);
    
    
    
    puts("\n ---------\ninserrisco un singolo elemento e vedo se l'iterator va");
    
    codaPushNum(C, 4);
    
    puts("Iteratore avanti");
    I=codaIteratorInit(C, NULL, FORWARD_ITERATION);

    while ((x=coda_NextNum(I))!=CODA_ITERATION_END) {
        printf(">%d\n",(int)x);
    }
    
    codaIteratorFree(I);
    puts("\n ---------\n");
    
    codaFree(C);
    
    return;
}




























