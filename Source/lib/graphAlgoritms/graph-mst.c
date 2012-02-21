//
//  graph-mst.c
//  MicLibApa2010
//
//  Created by mic on 21/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "coda.h"

#include "graph-mst.h"
#include "union-find.h"
#include "heap.h"

#warning need to be tested

graph kruskal(graph G, float (*pesoArco )(void *)){
    int         nNodes  = graphCountNodes(G);
    graph       GF       = graphInit(nNodes, GRAPH_IS_NOT_ORIENTED); // e gli orientati??
    uf_handler  uf      = uf_init(graphGetMaxNodes(G));

    archInfo arco;
    
    coda allArcs=graphGetAllArchs(G);
    heap archHeap=heapInit(nNodes, pesoArco, HEAP_GET_MIN);
    
    while ((arco=codaGet(allArcs))!=NULL) {
        heapInsert(archHeap, arco);
    }
    
    int from, to;
    
    while ((arco= heapExtract(archHeap))!=NULL) {
        from=arco->fromNode;
        to= arco->toNode;
        
        if (uf_find(uf,from , to)) {
            uf_unionFind(uf, from, to);
            
            graphAddNode(GF, from, arco->fromInfo);
            graphAddNode(GF, to, arco->toInfo);
            graphAddArch(GF, from, to, arco->archInfo); 
        }
    }
    
    return GF;
    
}