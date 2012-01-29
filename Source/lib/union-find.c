//
//  union-find.c
//  MicLibApa2010
//
//  Created by mic on 16/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "union-find.h"
#include <string.h>

#define max(a,b) ( (a>b)? a: b )

// local function
static int uf_checkIfSizeFitsAndAdjust(uf_handler_t H, int p, int q);

struct uf_handler_s {
    int *id;
    int *size;
    int max_len;
    int len;
};

#define UF_DEFAULT_LEN 1000

uf_handler_t uf_init(int max_len){
    if (max_len<2) {
        puts("Using default len because size <2");
        max_len=UF_DEFAULT_LEN;
    }
    printf("lunghezza(max_len)=%d",max_len);
    
    uf_handler_t H;
    H=malloc(sizeof(struct uf_handler_s));
    H->len=0;
    H->max_len=max_len;
    H->id=calloc(max_len, sizeof(int));
    H->size= calloc(max_len, sizeof(int));
    
    //initialize
    for (int i=0; i<max_len; i++) {
        H->id[i]=i;
        H->size[i]=0;
    }
    
    return H;
}

// chech if nubers fits tu already allocated arrays, if not realloc the struct: SO BE CAREFUL: use H->max_len and H->id, size ONLY after che check!
int uf_checkIfSizeFitsAndAdjust(uf_handler_t H, int p, int q)
{
    int max= max(p, q);
    int max_len_tmp;
    
    //printf("il massimo tra %d e %d è %d", p, q, max);
    if ( max < H->max_len ) 
        return 0;
    else{
        puts("\nunion find: riallocazione dei vettori a causa delle dimensioni ecessive");
        printf("vecchia dimensione: %d \n", H->max_len);
        
        if (max >= 2* H->max_len) {
            max_len_tmp =(int)(max*1.5);
        }else{
            max_len_tmp = 2 * H->max_len;
        }
        
        H->id   = (int *)realloc(H->id,   sizeof(int)* max_len_tmp);
        H->size = (int *)realloc(H->size, sizeof(int) *max_len_tmp);
        
        H->max_len=max_len_tmp;
        
        printf("nuova dimensione: %d  \n", H->max_len);
        return 1;
    }
    
}

int uf_find(uf_handler_t H, int p, int q){
    int i,j;
    int *id;;
    
    
    uf_checkIfSizeFitsAndAdjust(H, p, q);
    
    id = H->id;
    
    //con dimezzamento
    for ( i=p; i!=id[i]; id[i]=id[ id[i] ], i=id[i]);
    for ( j=q; j!=id[j]; id[j]=id[ id[j] ], j=id[j]);
    
    if (i == j) return 1;  // found
    else    return 0;       // not found
}

int uf_unionFind(uf_handler_t H, int p, int q){
    int i,j;
    int *id, *size;
    
    uf_checkIfSizeFitsAndAdjust(H, p, q);
    id = H->id;
    size=H->size;
    
    //con dimezzamento
    for ( i=p; i!=id[i]; id[i]=id[ id[i] ], i=id[i]);
    for ( j=q; j!=id[j]; id[j]=id[ id[j] ], j=id[j]);
    
    if (i == j) return 1;
    
    // pesato: agglinge il ramo piccolo a quello grande
    if ( size[i] < size[j] ) {
        id[i]=j;
        size[j] += size[i];
    }else{
        id[j]=i;
        size[i] += size[j];
    }
    
    H->len++;
    return 0;
}

void uf_free(uf_handler_t H){
    free(H->size);
    free(H->id);
    free(H);
}

void uf_selftest(void){

    uf_handler_t H = uf_init(4);
    uf_unionFind(H, 1, 4);
    uf_unionFind(H, 1, 9);
    uf_unionFind(H, 1, 20);
    
    if (uf_find(H, 4, 7)) {
        puts("trovato");
    }else   
        puts("NON trovato");

    uf_free(H);
}



/*
 int qfind(int p, int q, int *id);
 int qunion(int p, int q, int *id);
 int qunion23(int p, int q, int *id,int *size);
 
 #define N 10000
 void selftest1(void){
 
 for (int j=0; j<2; j++, puts("detro"),  puts("d2"))
 puts("fuori");
 
 
 puts("starting union find test");
 
 int i,p,q,id[N], sz[N];
 
 for (i=0; i<N; id[i]=i, sz[i]=1, i++) ;
 
 while (scanf("%d %d", &p,&q)==2) 
 {
 ///
 if (id[p]==id[q]) continue;
 for (t = id[p], i=0 ; i<N ; i++) 
 if (id[i] == t) id[i]=id[q];
 ///
 //if (!qfind(p, q, id))
 
 if (!qunion23(p, q, id,sz))
 //if (!qunion(p, q, id))
 printf(" %d %d\n", p,q);
 }
 }
 
 int qfind(int p, int q, int *id){
 //int i,t;
 if (id[p]==id[q]) return 1;
 for (int tmp = id[p] , i=0 ; i<N ; i++) 
 if (id[i] == tmp) id[i]=id[q];
 return 0;
 }
 
 int qunion(int p, int q, int *id){
 int i,j;
 for ( i=p; i != id[i]; i=id[i]);
 for ( j=q; j != id[j]; j=id[j]);
 if (i == j) 
 return 1;
 id[i]=j;
 return 0;
 }
 
 int qunion23(int p, int q, int *id,int *size){
 int i,j;
 
 //con dimezzamento
 for ( i=p; i!=id[i]; id[i]=id[ id[i] ], i=id[i]);
 for ( j=q; j!=id[j]; id[j]=id[ id[j] ], j=id[j]);
 
 if (i == j) return 1;
 
 // pesato: agglinge il ramo piccolo a quello grande
 if ( size[i] < size[j] ) {
 id[i]=j;
 size[j] += size[i];
 }else{
 id[j]=i;
 size[i] += size[j];
 }
 
 return 0;
 }*/

