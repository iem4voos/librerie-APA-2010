//
//  str2int.c
//  MicLibApa2010
//
//  Created by mic on 14/08/11.
/*
 use a string array to contain strings
 
 initialized with some size, realloc che size if dimension excede array len
 
 use realloc, so if you need to use on small memory system need to change che alloc mode
 */



#include "str2int.h"
#include <stdlib.h>
#include <string.h>

struct s2i_s {
    char ** s2i_vett;
    int len;
    int max_lenght;
};

s2i str2intInit(int size){
    struct s2i_s * s;
    s=malloc(sizeof(struct s2i_s));
    
    s->s2i_vett=calloc(size, sizeof(char *) );
    s->max_lenght = size;
    
    if (s->s2i_vett==NULL) {
        fprintf(stderr, "\n !!cannot allocate enaught memory to initialize str2init Lib !\n");
        return NULL;
    }
    
    s->len=0;
    return s;
}

int str2int(s2i S,char *string){
    int len=S->len;
    
    // non funziona bene e in fase di esecuzione provoca la mancanza del output
    if (S->max_lenght <= len) {
        puts("riallocazione del vettore causa dimensione eccessiva...");
        S->s2i_vett=realloc(S->s2i_vett, sizeof(char *) *  len*2);
        if (S->s2i_vett==NULL) {
            fprintf(stderr, "\nerrore di RiAllocazione del vettore in seguito all aumento della dimensione\n");
            return -1;
        }else{
            S->max_lenght = len * 2 ;
        }
    }
    
    // serch for the string
    for(int i =0; i < len ; i++){
        if(!strcmp(string, S->s2i_vett[i]))
            return i;
    }
    
    // if no string found create one
    S->s2i_vett[len]=strdup(string);
    S->len ++;
    
    return len;
}

// getters and setters

int str2intLen(s2i S){
    return S->len;
}

void str2intPrint(s2i S)
{    
    puts("printing content..");
    for (int i=0; i< S->len; i++) {
        printf("[%2d]-|%s|\n",i, S->s2i_vett[i]);
    }
}

char *  int2str(s2i S, int num){
    return S->s2i_vett[num];
}

// dealloc

void    str2intFree(s2i S)
{    
    for (int i=0; i< S->len; i++) {
        free(S->s2i_vett[i]);
    }
    free(S->s2i_vett);
    free(S);
}
