//
//  graph-Bfs.h
//  MicLibApa2010
//
//  Created by mic on 31/01/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MicLibApa2010_graph_Bfs_h
#define MicLibApa2010_graph_Bfs_h

/* used in distance array */
#define INFINITE_DISTANCE INT_MAX
/* used in father array to indicate orphan or non node */
#define NOT_A_NODE -1

#include "graph.h"

typedef enum color_e  {
    WHITE,
    GRAY,
    BLACK
} color_t;

typedef struct bfs_resut_s {
    graph graph;
    int startEdge;
    int nEdges;
    int *distance;
    int *father;
    int *colors;
} * bfs_result;

bfs_result  bfs_init(graph G);
void bfsFreeResult(bfs_result R);

bfs_result bfs_from(bfs_result handler, int fromEdge);

void print_bfs_res(bfs_result R);
void bfs_selftest1(void);

#endif
