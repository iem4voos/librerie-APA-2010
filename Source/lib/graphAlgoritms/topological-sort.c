//
//  topological-sort.c
//  MicLibApa2010
//
//  Created by mic on 31/01/12. All rights reserved.

#include <stdio.h>
#include "topological-sort.h"
#include "graph-dfs.h"

#pragma mark - ALGORITMS
#pragma mark - Topological sort (dfs)

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