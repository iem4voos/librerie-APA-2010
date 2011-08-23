//
//  graph.h
//  MicLibApa2010
//
//  Created by mic on 21/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef MicLibApa2010_graph_h
#define MicLibApa2010_graph_h

#define Mic_graph_USE_ADJ_LIST 1

//#include "coda.h"

typedef struct graph_s * graph;

graph graphInit(int nEdges, int isOriented, int isWeithed);
int   graphAddEdge(graph, int edge, void *edgeInfo);
void  graphDelEdge(graph G, int edge);

void  graphAddArch(graph G, int fromEdge, int toEdge, void *archInfo);
void  graphDelArch(graph G, int fromEdge, int toEdge);


int graphCountEdges(graph G);
int * graphGetEdges(graph);
int * graphGetArchsFrom(graph, int Edge);

void graph_selftest1(void);

#endif
