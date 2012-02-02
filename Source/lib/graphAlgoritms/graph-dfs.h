//
//  dfs.h
//  MicLibApa2010
//
//  Created by mic on 31/01/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MicLibApa2010_dfs_h
#define MicLibApa2010_dfs_h

#include "graph.h"

typedef struct dfs_resut_s  * dfs_result;


typedef enum color_e  {
    WHITE,
    GRAY,
    BLACK
} color_t;

typedef struct dfs_resut_s {
    graph graph;
    int startEdge;
    int nEdges;
    int *father;    // Pi
    int *discover;     //d
    int *fine;          //f
    int *colors;
    int time;  // local global time counter
    //----
    
    void (*funcPtr)(int, void *);
    void * somePtToFunc;
    
} * dfs_result_t;

dfs_result  dfs_init(graph G);

dfs_result dfs(dfs_result handler);

dfs_result dfs_visit_r(dfs_result handler,int fromEdge);
dfs_result dfs_initWithFuncAndPt(graph G, void (*func)(int vistedNode, void *), void * somePtr);



#endif
