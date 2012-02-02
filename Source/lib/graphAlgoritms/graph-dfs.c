//
//  dfs.c
//  MicLibApa2010
//
//  Created by mic on 31/01/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "coda.h"
#include "graph-dfs.h"

#define NAN INT_MIN
#define MAX_INT INT_MAX




dfs_result_t dfs_visit_r(dfs_result_t H,int fromEdge);

#pragma mark - DFS

void dfsResetColorFatherTime(dfs_result H, color_t color ){
    
    int nEdges=graphCountNodes(H->graph);
    
    for (int i=0; i < nEdges; i++) {
        H->colors  [i] = color;
        H->father  [i] = NAN;
    }
    H->time=0;
}

dfs_result_t  dfs_init(graph G){
    struct dfs_resut_s * s;
    int nEdges=graphGetMaxNodes(G);
    
    s=malloc(sizeof(struct dfs_resut_s));
    s->graph=G;
    s->nEdges=nEdges;
    s->time=0;
    
    s->fine     = calloc(nEdges, sizeof(int));
    s->discover = calloc(nEdges, sizeof(int));
    s->colors   = calloc(nEdges, sizeof(int));
    s->father   = calloc(nEdges, sizeof(int));
    
    for (int i=0; i < nEdges; i++) {
        s->colors  [i] = WHITE;
        //s->discover[i] = NAN;       // nu
        //s->fine    [i] = MAX_INT;   //nu (vengono scritti dopo)
        s->father  [i] = NAN;
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

dfs_result_t dfs(dfs_result_t handler){
    
    int nNodes=graphGetMaxNodes(handler->graph);
    
    for (int i=0; i< nNodes ; i++) {
        
        if (0==graphNodeExist(handler->graph, i)) {
            continue;
        }
        
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
    
    H->colors  [fromEdge] = GRAY;
    H->discover[fromEdge] = ++(H->time);
    
    nArcs= graphCountArchsFromNode(G, fromEdge);
    //if (nArcs!=0) 
    arcs = graphGetArchsFromNode(G, fromEdge);
    
    for (int i=0; i<nArcs; i++) {
        next= arcs[i];
        if (H->colors[next]==WHITE ) {
            H->father[next]=fromEdge;
            dfs_visit_r(H, next);
        }
    }
    
    if (H->funcPtr!=NULL) {
        //puts(".. ptr not null");
        H->funcPtr(fromEdge, H->somePtToFunc);
    }
    
    H->colors[fromEdge]=BLACK;
    H->fine[fromEdge]=++H->time;
    
    return H;
}

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
