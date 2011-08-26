//
//  graph-algoritm-test.c
//  MicLibApa2010
//
//  Created by mic on 24/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
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

void zBFS(graph G, int fromEdge){
    color_t * colors;
    int *d;
    int *p;
    coda C;
    
    int x;
    int *tmpVet;
    
    int nEdges= graphCountEdges(G);
    colors=calloc(nEdges, sizeof(color_t));
    d= calloc(nEdges, sizeof(int));
    p= calloc(nEdges, sizeof(int));
    
    
    
    for (int i=0; i< nEdges; i++) {
        colors[i]=WHITE;
        p[i]=NAN;
        d[i]=MAX_INT;
    }
    colors[fromEdge]=GRAY;
    d[fromEdge]=0;
    
    C=codaInitNumeric();
    codaPushNum(C, (int)fromEdge);
    
    while (codaCount(C) != 0) {
        
        x = (int)codaGetNum(C);
        
        tmpVet= graphGetArchsFromEdge(G, x);
        for (int i=0; i< graphCountArchsFromEdge(G, x); i++) {
            if (colors[i]==WHITE) {
                colors[i]=GRAY;
                d[i]=d[i]+ 1;     // might be th distance x,i ??
                p[i]=x;
                codaPushNum(C, i);
            }
        }
        
        colors[x]=BLACK;
    }
}
