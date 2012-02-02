//
//  topological-sort.c
//  MicLibApa2010
//
//  Created by mic on 31/01/12. All rights reserved.

#include <stdio.h>
#include "topological-sort.h"
#include "graph-dfs.h"
#include "coda.h"

#pragma mark - ALGORITMS
#pragma mark - Topological sort (dfs)

void tsLc(int edgeNUm, void *b){
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

//MARK: selftest

coda topological_sort_SelfTest(graph Gin){
    graph G=graphInit(9, GRAPH_IS_ORIENTED);
    
    for (int i=1; i<10; graphAddNode(G, i, NULL), i++);
    
    //graphAddArch(G, 0, 1, NULL);
    graphAddArch(G, 1, 2, NULL);
    graphAddArch(G, 2, 8, NULL);
    graphAddArch(G, 3, 2, NULL);
    graphAddArch(G, 3, 7, NULL);
    graphAddArch(G, 7, 8, NULL);
    
    graphAddArch(G, 4, 5, NULL);

    coda C=topological_sort(G);
    coda_iterator I=codaIteratorInit(C, NULL, FORWARD_ITERATION);
    int x;
    while ((x=coda_NextNum(I))!=CODA_ITERATION_END) 
        printf(">%d\n",(int)x);
    
    codaIteratorFree(I);
    
    puts("\n ---------\n");
    
    return NULL;
    
}