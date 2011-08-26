//
//  heap.c
//  MicLibApa2010
//
//  Created by mic on 25/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ranlib.h>
#include "heap.h"

#define DEBUG 1

#define HEAP_DEF_SIZE 10
#define HEAP_GROW_FACTOR 2

#define LEFT(i)   	((i*2) + 1)
#define RIGHT(i)	((i*2) + 2)
#define PARENT(i)	((i-1) / 2)

typedef struct heap_bin_s {
    int heapSize;
    int maxSize;
    void **array;
    int (*keyOf)(void *);
} * heap_bin_t;

/*  ----  Local Functions -------*/
#pragma mark - local prototypes
void test_print_item(void * x);
void heapBuild (heap_bin_t H);
void heapSwap(heap_bin_t H, int n1, int n2);
void heapHeapify(heap_bin_t H, int i);
void heapBuild (heap_bin_t H);
int heap_checkSizeOrGrow(heap H);


#pragma mark - Functions

heap_bin_t heapInit(int size,int (*keyOfElement )(void *)){
    
    heap_bin_t H;
    
    if( size < HEAP_DEF_SIZE )
        size = HEAP_DEF_SIZE;
    
    H=malloc(sizeof(struct heap_bin_s));
    
    if (H==NULL) {
        puts("\nheap: ERRRORE ALLOCAZIONE MEMORIA\n");
        return NULL;
    }
    
    H->keyOf=keyOfElement;
    H->maxSize=size;
    H->heapSize=0;
    H->array= calloc(size, sizeof(void *));
    
    if (H->array==NULL) {
        puts("\nheap: ERRRORE ALLOCAZIONE MEMORIA\n");
        return NULL;
    }
    
    return H;
}


void heapSwap(heap_bin_t H, int n1, int n2)
{
	void *	temp;
    void **v=H->array;
    
	temp  = v[n1];
	v[n1] = v[n2];
	v[n2] = temp;
    
    //printf("heap: scambiati %d e %d ", n1,n2);
	return;
}    


int heap_checkSizeOrGrow(heap H){
    
    void ** tmp;
    int newsize;
    
    if (H->heapSize +2 >= H->maxSize) 
    {
        newsize = H->maxSize * HEAP_GROW_FACTOR;
        tmp=realloc(H->array,sizeof(void *) * newsize );
        if (tmp==NULL) {
            puts("heap: errore riallocazione vettore");
            return EXIT_FAILURE;
        }else{
        
            if(DEBUG) printf("\nheap: vettore riallocato da %d a %d", H->maxSize , newsize);
            H->array=tmp;
            H->maxSize = newsize;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}

void heapInsert(heap_bin_t H, void * element)
{
	int i;
    int (*key)(void *)=H->keyOf;
    void **A;
    
    heap_checkSizeOrGrow(H);
    
    A=H->array;
    
 	i = H->heapSize++;
    //printf("proto dimensione heap a %d, i= %d", H->heapSize,i);
    
    while(i>=1 && key(A[PARENT(i)])<key(element)   )
    {
        A[i] = A[PARENT(i)];
        //printf("\n scambio a[%d]con a[%d] perche %d > %d",i, PARENT(i), key(element), key(A[PARENT(i)]) );
        //i = (i-1)/2;
        i=PARENT(i);
        //printf("\n i= %d ", PARENT(i));
    }
	A[i] = element;
    /*printf("\n metto l'elemento");
    //test_print_item(element);
    printf(" in pos %d\n",i);
     */
    
    heapBuild(H);
	return;
}


void heapHeapify(heap_bin_t H, int i)
{
    int l, r, largest;
    int heapsize=H->heapSize;
    void **A=H->array;
    int (*key)(void *)=H->keyOf;
    
    l = LEFT(i);
    r = RIGHT(i); 
    
    if ( l < heapsize && key(A[l])>key(A[i])) 
        largest=l;
    else largest = i;
    
    if (r < heapsize && key(A[r])>key(A[largest])) 
        largest=r;
    
    if (largest != i) {
		heapSwap(H,i,largest);
		heapHeapify(H,largest);
    }
    return;
} 

void heapBuild (heap_bin_t H)
{
	int i;
    int heapsize=H->heapSize;
    
	for (i=(heapsize)/2-1; i >= 0; i--){
		heapHeapify(H,i);
	}
	return;
}

void * heapExtractMax(heap_bin_t H){
    void * x;
    void **A=H->array;
    
    x=A[0];
    A[0]=A[H->heapSize];
    H->heapSize--;
    
    heapBuild(H);
    
    return x;
};

#pragma mark - TEST

void test_print_item(void * x){
    int *pt,num=99;
    pt=x;
    num=*pt;
    printf("|%d ", num);
    
}

void test_print_array_int(heap_bin_t H){
    for(int i=0 ; i< H->heapSize ; i++){
        test_print_item(H->array[i]);
    }
    puts("\n");
}

int testKeyOf(void *elem){
    int *x,num;
    x=elem;
    if (elem==NULL) {
        return 0;
    }
    num=*x;
    
    return num;
}

#define ZZZ 100
void heapSelf(void){
    puts("HEAP SELFTEST\n");
    
    heap_bin_t H;
    H=heapInit(10, testKeyOf);
    
    int testArray[ZZZ+3];
    
    sranddev();
    for (int i=ZZZ; i>=0; i--) {
        testArray[i]=rand()%99+1;
        //puts("-----------");
        //test_print_array_int(H);
        heapInsert(H, &testArray[i]);
        //test_print_array_int(H);
    }
    
    puts("+++++++++++++++");
    
    for (int i=0; i< ZZZ; i++)
        printf("<-- %d\n", *((int *)heapExtractMax(H)));
     
    
    puts(" end: HEAP SELFTEST\n");
    
}

