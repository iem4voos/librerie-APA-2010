//
//  graph-mst.h
//  MicLibApa2010
//
//  Created by mic on 21/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MicLibApa2010_graph_mst_h
#define MicLibApa2010_graph_mst_h

#include "graph.h"

// float (*pesoArco )(void *) prende in ingresso una struttura
/*
 
 typedef struct archInfo_s{
 void * fromInfo;
 void * archInfo;
 void * toInfo;
 } *archInfo;
 */

graph kruskal(graph G, float (*pesoArco )(void *));

#endif
