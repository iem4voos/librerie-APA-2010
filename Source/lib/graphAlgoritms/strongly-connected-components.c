//
//  strongly-connected-components.c
//  MicLibApa2010
//
//  Created by mic on 3/01/12.

#include <stdio.h>
#include "strongly-connected-components.h"
#include "graph-dfs.h"


void insertInCoda(int visitedNode, void *Co){
    coda C=(coda)Co;
    codaPushNum(C, visitedNode);
}

coda striclyConnected(graph G){
    // discutibile.. invece di max nodes count nodes?
    //uf_handler UF = uf_init( graphGetMaxNodes(G) );
    graph      GT;
    
    dfs_result r1, r2;
    
    r1=dfs_init(G);
    
    // 1- visit
    r1=dfs(r1);
    
    // 2- transpose the graph
    GT = graphTranspose(G);
    
    //run  Dfs on Gt but considering them in inverse "fine visita" time
    
    coda C=codaInitNumeric();
    r2=dfs_initWithFuncAndPt(G, insertInCoda, C);
    
    
    //return the forest
    
    
    
    
    
    int *nodes=graphGetNodes(G);
    int nodeCount=graphCountNodes(G);
        
    
    r1=dfs_initWithFuncAndPt(G, insertInCoda, C);
    
    
    for (int i=0; i< nodeCount; i++) {
        if (r1->colors[nodes[i]]==WHITE) {
            dfs_visit_r(r1, nodes[i]);
        }
    }
    
    
    
    
    graphFree(GT);
    return NULL;
}