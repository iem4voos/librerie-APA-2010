//
//  graph-Bfs.c
//  MicLibApa2010
//
//  Created by mic on 31/01/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "coda.h"
#include "graph.h"

#define NAN -2147483648
#define MAX_INT 2147483647

typedef enum color_e  {
    WHITE,
    GRAY,
    BLACK
} color_t;

typedef struct bfs_resut_s {
    graph graph;
    int startEdge;
    int nEdges;
    int *distance;
    int *father;
    int *colors;
} * bfs_result_t;

#pragma mark - BFS

bfs_result_t  bfs_init(graph G){
    struct bfs_resut_s * s;
    int nEdges=graphCountNodes(G);
    
    s=malloc(sizeof(struct bfs_resut_s));
    s->graph=G;
    s->nEdges=nEdges;
    
    s->distance= calloc(nEdges, sizeof(int));
    s->father  = calloc(nEdges, sizeof(int));
    s->colors  = calloc(nEdges, sizeof(int));
    
    for (int i=0; i < nEdges; i++) {
        s->colors[i]=WHITE;
        s->father[i]=NAN;
        s->distance[i]=MAX_INT;
    }
    
    return s;
}

//dfs_setWeight(dfs_result_t *, );




void bfsFreeResult(bfs_result_t R){
    free(R->colors);
    free(R->father);
    free(R->distance);
}

bfs_result_t bfs_from(bfs_result_t handler, int fromEdge){
    int *d=handler->distance;
    int *p=handler->father;
    int *colors=handler->colors;
    int x, *tmpVet;
    coda C;
    graph G=handler->graph;
    
    colors[fromEdge]=GRAY;
    d[fromEdge]=0;
    
    C=codaInitNumeric();
    codaPushNum(C, (int)fromEdge);
    
    while (codaCount(C) != 0) {
        
        x = (int)codaGetNum(C);
        int arcsFromX=graphCountArchsFromNode(G, x);
        
        if (arcsFromX > 0) {
            tmpVet= graphGetArchsFromNode(G, x);
        }
        
        for (int i=0; i< arcsFromX ; i++) {
            if (colors[i]==WHITE) {
                colors[i]=GRAY;
#warning distance??                
                d[i]=d[i]+ 1;     // might be th distance x,i ??
                p[i]=x;
                codaPushNum(C, i);
            }
        }
        colors[x]=BLACK;
    }
    return handler;
}

void print_bfs_res(bfs_result_t R){
    
    puts("\n/*---- Start Print BFS RESULT-----*/");
    puts("Colors:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%2d", R->colors[i]);
    }
    puts("\nDistances:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%2d", R->distance[i]);
    }
    puts("\nFathers:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%2d", R->father[i]);
    }
    puts("\n/*---- END Print BFS RESULT-----*/");
}

//MARK: - SELFTEST

void bfs_selftest1(void){
    graph G;
    bfs_result_t  R;
   // dfs_result_t D;
    
    G=graph_selftest1();
    
    //bfs test
    /*
     R=bfs_init(G);
     print_bfs_res(R);
     
     R=bfs_from(R, 1);
     print_bfs_res(R);
     */
    
    // dfs test
    /*
     D=dfs_init(G);
     //print_Dfs_res(D);
     D=dfs(D, NULL);
     print_Dfs_res(D);
     */
    //++ topological sort test ++
    
    coda C;
    C= topological_sort(G);
    printf("coda topologica di N: %d %f\n", codaCount(C), CODA_ITERATION_END);
    
    
#if 0
    coda_iterator I;
    I=codaIteratorInit(C, NULL, FORWARD_ITERATION);
    int x;
    while ((x=coda_NextNum(I))!=CODA_ITERATION_END) 
        printf(">%d\n",(int)x);
    
    codaIteratorFree(I);
    
#endif
    
    puts("\n ---------\n");
    
    
}

