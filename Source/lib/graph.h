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

#include "coda.h"

/*
typedef enum is_graph_weithed_e {
    GRAPH_IS_WEIGHTD,
    GRAPH_IS_NOT_WEIGTHED
} is_graph_weithed;
*/


typedef enum is_graph_oriented_e {
    GRAPH_IS_ORIENTED,
    GRAPH_IS_NOT_ORIENTED
} is_graph_oriented;

typedef struct archInfo_s{
    void * fromInfo;
    void * archInfo;
    void * toInfo;
    int  fromNode;
    int  toNode;
} *archInfo;

typedef struct graph_s * graph;

//MARK: - Init Destroy and copy
graph graphInit(int nNodes, is_graph_oriented);
void graphFree(graph G);

graph graphCopy(graph G);
graph graphTranspose(graph G);

//MARK: Nodes
int    graphAddNode(graph, int edge, void *nodeInfo);
void   graphDelNode(graph G, int edge);
int  * graphGetNodes(graph);
void * graphGetNodeData(graph G, int nodeNum);
int    graphNodeExist(graph G, int node); // 1 if exist


//MARK: Arcs
int   graphAddArch(graph G, int fromNode, int toNode, void *archInfo);
void  graphDelArch(graph G, int fromNode, int toNode);
int * graphGetArchsToNode(graph, int node);
int * graphGetArchsFromNode(graph, int node); // int a dove arriva
void * graphGetArchData(graph G, int from, int to);
coda  graphGetAllArchs(graph G);

//MARK: Counters
int graphGetMaxNodes(graph G); //number of higest node
int graphCountNodes(graph G);  //effectiv nodes
int graphCountArchsFromNode(graph G, int edge);
int graphCountArchsToNode(graph G, int edge);

graph graph_selftest1(void);

#endif
