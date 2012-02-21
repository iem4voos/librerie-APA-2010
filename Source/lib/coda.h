//  coda.c  librerie-APA-2010   Created by mic on 08/09/10.



#ifndef coda_h
#define coda_h

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define DEBUG 1
#define CODA_ITERATION_END INT_MIN
#define CODA_FLOAT_ERROR INT_MIN

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

coda codaInit(void);
void codaFree(coda);
void codaFreeWithContent(coda C);

void codaPush(coda , void * elemento);
void * codaGet(coda);
void * codaPop(coda);

void codaPushUnique(coda , void *elem, int (*compare)(void *, void *));
void * codaSerch       
    (coda C, void * elem, int (*compare)(void *, void *));
void * codaDelByCompare
    (coda C, void * elem, int (*compare)(void *, void *));

int codaCount(coda);
int codaIsEmpty(coda C);


coda_iterator codaIteratorInit(coda C, void * element, enum iteration_direction);
void codaIteratorRewindFor(coda_iterator I,enum iteration_direction direction );
void codaIteratorFree(coda_iterator I);
void * coda_Next(coda_iterator I);
void * coda_Prev(coda_iterator I);

//numeric version----------

coda codaInitNumeric(void);
//void codaFree(coda);
void codaPushNum(coda C, float num);
float codaPopNum(coda C);
float codaGetNum(coda c);
float codaDelNum(coda , float);

float coda_NextNum(coda_iterator I);
float coda_PrevNum(coda_iterator I);

void coda_selfTest1(void);

#endif
