//  coda.h   librerie-APA-2010

#include <float.h>  
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1
#define CODA_ITERATION_END FLT_MIN

enum iteration_direction {
    FORWARD_ITERATION = 1,
    BACKWARD_ITERATION = 0
};

typedef struct coda_s * coda;
typedef struct iterator_s * coda_iterator;




/*
 Push-->
     +-+-+-+-+-+
     | | | | | |
     +-+-+-+-+-+
 <--Pop         Get-->
 
 */

//void codaAppend(coda , void * elemento);

coda codaInit(void);
void codaFree(coda);
void codaPush(coda , void * elemento);
void * codaGet(coda);
void * codaPop(coda);


int codaCount(coda);
int codaIsEmpty(coda C);

coda codaInitNumeric(void);
//void codaFree(coda);
void codaPushNum(coda C, float num);
float codaPopNum(coda C);
float codaGetNum(coda c);

coda_iterator codaIteratorInit(coda C, void * element, enum iteration_direction);
void * coda_Next(coda_iterator I);
void * coda_Prev(coda_iterator I);

float coda_NextNum(coda_iterator I);
float coda_PrevNum(coda_iterator I);

void coda_selfTest1(void);

