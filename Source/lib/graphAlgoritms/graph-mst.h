//
//  graph-mst.h
//  MicLibApa2010
//
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MicLibApa2010_graph_mst_h
#define MicLibApa2010_graph_mst_h

#include "graph.h"

typedef enum {MST_MIN,MST_MAX} mst_max_or_min;

// float (*pesoArco )(void *) prende in ingresso una struttura
/*
 
 typedef struct archInfo_s{
 void * fromInfo;
 void * archInfo;
 void * toInfo;
 } *archInfo;
 
 come definito in graph .h
 */

graph kruskal(graph G, float (*pesoArco )(void *), mst_max_or_min);

#endif

/* exaple of peso
 
 float peso(void * pt){
 archInfo a = pt; //cast to arch_handler 
 void  * archValue = a->archInfo;   //get the inserted info
 
 float peso= *((float *)archValue); //use the info
 return peso;
 };
 
 */
