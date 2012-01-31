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

/*
typedef enum is_graph_weithed_e {
    GRAPH_IS_WEIGHTD,
    GRAPH_IS_NOT_WEIGTHED
} is_graph_weithed;
*/

typedef enum{FROM,TO} from_or_to;

typedef enum is_graph_oriented_e {
    GRAPH_IS_ORIENTED,
    GRAPH_IS_NOT_ORIENTED
} is_graph_oriented;

typedef struct archInfo_s{
    void * fromInfo;
    void * archInfo;
    void * toInfo;
} *archInfo;

typedef struct graph_s * graph;

graph graphInit(int nNodes, is_graph_oriented);
void graphFree(graph G);

int   graphAddNode(graph, int edge, void *nodeInfo);
void  graphDelNode(graph G, int edge);

int   graphAddArch(graph G, int fromEdge, int toNode, void *archInfo);
void  graphDelArch(graph G, int fromEdge, int toNode);


int graphCountNodes(graph G);
int * graphGetNodes(graph);
int * graphGetArchsToNode(graph, int node);
int * graphGetArchsFromNode(graph, int node); // int a dove arriva

int graphCountArchsFromNode(graph G, int edge);
int graphCountArchsToNode(graph G, int edge);


graph graph_selftest1(void);

#endif
