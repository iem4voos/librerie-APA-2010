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

typedef enum is_graph_weithed_e {
    GRAPH_IS_WEIGHTD,
    GRAPH_IS_NOT_WEIGTHED
} is_graph_weithed;

typedef enum is_graph_oriented_e {
    GRAPH_IS_ORIENTED,
    GRAPH_IS_NOT_ORIENTED
} is_graph_oriented;


typedef struct graph_s * graph;

graph graphInit(int nEdges, is_graph_oriented , is_graph_weithed);

int   graphAddEdge(graph, int edge, void *edgeInfo);
void  graphDelEdge(graph G, int edge);

int   graphAddArch(graph G, int fromEdge, int toEdge, void *archInfo);
void  graphDelArch(graph G, int fromEdge, int toEdge);


int graphCountEdges(graph G);
int * graphGetEdges(graph);
int * graphGetArchsFromEdge(graph, int Edge); // int a dove arriva

int graphCountArchsFromEdge(graph G, int edge);
int graphCountArchsToEdge(graph G, int edge);

#warning graph free missing

graph graph_selftest1(void);

#endif
