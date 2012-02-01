//
//  graph-Bfs.c
//  MicLibApa2010
//
//  Created by mic on 31/01/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "coda.h"

#include "graph-Bfs.h"


#define NAN INT_MIN
#define MAX_INT INT_MAX



#pragma mark - BFS

bfs_result  bfs_init(graph G){
    struct bfs_resut_s * s;
    int nEdges=graphGetMaxNodes(G);
    
    s=malloc(sizeof(struct bfs_resut_s));
    s->graph=G;
    s->nEdges=nEdges;
    
    s->distance= calloc(nEdges, sizeof(int));
    s->father  = calloc(nEdges, sizeof(int));
    s->colors  = calloc(nEdges, sizeof(int));
    
    for (int i=0; i < nEdges; i++) {
        s->colors[i]=WHITE;
        s->father[i]=NOT_A_NODE;
        s->distance[i]=INFINITE_DISTANCE;
    }
    return s;
}

void bfsFreeResult(bfs_result R){
    free(R->colors);
    free(R->father);
    free(R->distance);
}

bfs_result bfs_from(bfs_result handler, int fromEdge){
    
    coda C;
    graph G=handler->graph;
    int *distance=handler->distance, *father=handler->father, *colors=handler->colors;
    int thisNode, *sons, nArcs, nextNode;
    
    colors  [fromEdge] = GRAY;
    distance[fromEdge] = 0;
    
    C=codaInitNumeric();
    codaPushNum(C, fromEdge);
    
    while (codaCount(C) != 0) {
        thisNode = codaGetNum(C);
        
        nArcs = graphCountArchsFromNode(G, thisNode);
        sons  = graphGetArchsFromNode(G, thisNode);  // if sons is null then the for will not run
        
        for (int i=0; i< nArcs ; i++) {
            nextNode=sons[i];
            if (colors[nextNode]==WHITE) {
                colors[nextNode]=GRAY;               
                distance[nextNode] = distance[thisNode]+1; 
                father[nextNode] = thisNode;
                codaPushNum(C, nextNode);
            }
        }
        colors[thisNode]=BLACK;
    }
    return handler;
}

void print_bfs_res(bfs_result R){
    
    puts("\n/*---- Start Print BFS RESULT-----*/");
    puts("Colors:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%5d", R->colors[i]);
    }
    puts("\nDistances:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%5d", (R->distance[i]==INFINITE_DISTANCE)? -1 : R->distance[i] );
        //printf("|%5d", R->distance[i] );
    }
    puts("\nFathers:");
    for (int i=0; i< R->nEdges; i++) {
        printf("|%5d", R->father[i]);
    }
    puts("\n/*---- END Print BFS RESULT-----*/");
}

//MARK: - SELFTEST -

void bfs_selftest1(void){
    graph G;
    bfs_result  R;
    
    //G=graph_selftest1();
    
    G=graphInit(1, GRAPH_IS_ORIENTED);
    for (int i=0; i< 5; i++) { graphAddNode(G, i*2, NULL);}
    graphAddArch(G, 0  , 1*2  , NULL);
    graphAddArch(G, 0  , 2*2, NULL);
    graphAddArch(G, 1*2  , 3*2, NULL);
    graphAddArch(G, 3*2, 4*2, NULL);
    
    
    //bfs test
     R=bfs_init(G);
    
     print_bfs_res(R);
     R=bfs_from(R, 0);
     print_bfs_res(R);
    
    bfsFreeResult(R);

    
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

