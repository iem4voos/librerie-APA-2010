//
//  graph-algoritm-test.c
//  MicLibApa2010
//
//  Created by mic on 24/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "coda.h"
#include "graph.h"
#include "graph-algoritm-test.h"

#define NAN -10000
#define MAX_INT 100000

#include "coda.h"

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

typedef struct dfs_resut_s {
    graph graph;
    int startEdge;
    int nEdges;
    int *father;    // Pi
    int *discover;     //d
    int *fine;          //f
    int *colors;
    int time;  // local global time counter
    //----
    
    void (*funcPtr)(int, void *);
    void * somePtToFunc;
    
} * dfs_result_t;


// local prototypes

dfs_result_t  dfs_init(graph G);
dfs_result_t dfs(dfs_result_t );


#pragma mark - BFS

bfs_result_t  bfs_init(graph G){
    struct bfs_resut_s * s;
    int nEdges=graphCountEdges(G);
    
    s=malloc(sizeof(struct bfs_resut_s));
    s->graph=G;
    s->nEdges=nEdges;
    
    s->distance=calloc(nEdges, sizeof(int));
    s->father=calloc(nEdges, sizeof(int));
    s->colors=calloc(nEdges, sizeof(int));
    
    for (int i=0; i < nEdges; i++) {
        s->colors[i]=WHITE;
        s->father[i]=NAN;
        s->distance[i]=MAX_INT;
    }
    
    return s;
}

dfs_result_t  dfs_initWithFuncAndPt(graph G, void (*func)(int, void *), void * somePtr){
    struct dfs_resut_s * s;
    s=dfs_init(G);
    s->funcPtr=func;
    s->somePtToFunc=somePtr;
    
    return s;
}


dfs_result_t  dfs_init(graph G){
    struct dfs_resut_s * s;
    int nEdges=graphCountEdges(G);
    
    s=malloc(sizeof(struct bfs_resut_s));
    s->graph=G;
    s->nEdges=nEdges;
    s->time=0;
    
    s->fine=calloc(nEdges, sizeof(int));
    s->discover=calloc(nEdges, sizeof(int));
    s->colors=calloc(nEdges, sizeof(int));
    s->father=calloc(nEdges, sizeof(int));
    
    for (int i=0; i < nEdges; i++) {
        s->colors[i]=WHITE;
        s->discover  [i]=NAN; // nu
        s->fine[i]=MAX_INT;     //nu (vengono scritti dopo)
        s->father  [i]=NAN;
    }
    
    return s;
}

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
        int arcsFromX=graphCountArchsFromEdge(G, x);
        
        if (arcsFromX > 0) {
            tmpVet= graphGetArchsFromEdge(G, x);
        }
        
        for (int i=0; i< arcsFromX ; i++) {
            if (colors[i]==WHITE) {
                colors[i]=GRAY;
                d[i]=d[i]+ 1;     // might be th distance x,i ??
                p[i]=x;
                codaPushNum(C, i);
            }
        }
        colors[x]=BLACK;
    }
    return handler;
}

// topological sort

#pragma mark - Topological sort


void tsLc(int edgeNUm, void *b){
    coda C;
    C=(coda)b;
    codaPushNum((coda)b, edgeNUm);
    
    printf("\ninserisco nella coda  %d\n", edgeNUm);
}

coda topological_sort(graph G){
    coda C;
    C=codaInitNumeric();
    
    dfs_result H;
    H=dfs_initWithFuncAndPt(G, tsLc, C);
    dfs(H);
    
    return C;
}

///---------- dfs-----


#pragma mark - DFS

dfs_result_t dfs(dfs_result_t handler){
    
    int * edges;
    edges= graphGetEdges(handler->graph);
    
    for (int i=0; i< graphCountEdges(handler->graph); i++) {
        if (handler->colors[i]== WHITE) 
            dfs_visit_r(handler, i);
        
    }
    return handler;
}


dfs_result_t dfs_visit_r(dfs_result_t H,int fromEdge)
{
    int * arcs, nArcs;
    graph G= H->graph;
    int next;
    
    H->colors[fromEdge]=GRAY;
    H->discover[fromEdge]=++H->time;
    
    nArcs= graphCountArchsFromEdge(G, fromEdge);
    //if (nArcs!=0) 
        arcs = graphGetArchsFromEdge(G, fromEdge);
    
    for (int i=0; i<nArcs; i++) {
        next= arcs[i];
        if (H->colors[next]==WHITE ) {
            H->father[next]=fromEdge;
            dfs_visit_r(H, next);
        }
    }
    
    if (H->funcPtr!=NULL) {
        puts(".. ptr not null");
        H->funcPtr(fromEdge, H->somePtToFunc);
    }
    
    H->colors[fromEdge]=BLACK;
    H->fine[fromEdge]=++H->time;
    
    return H;
}


#pragma mark -

void print_Dfs_res(dfs_result_t R){
    puts("\n/*---- Start Print DFS RESULT-----*/");
    puts("Fathers:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%2d", R->father[i]);
    }
    puts("\nDiscover time:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%2d", R->discover[i]);
    }
    puts("\nend time:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%2d", R->fine[i]);
    }
    puts("\n/*---- END Print DFS RESULT-----*/");

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

void bfs_selftest1(void){
    graph G;
    bfs_result_t  R;
    dfs_result_t D;
    
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

#pragma mark - alg

