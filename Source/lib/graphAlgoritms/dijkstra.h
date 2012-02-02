//
//  dijkstra.h
//  MicLibApa2010
//
//  Created by mic on 3/01/12.


#ifndef MicLibApa2010_dijkstra_h
#define MicLibApa2010_dijkstra_h

#include <limits.h>
#include "graph.h"
#include "coda.h"

#ifndef INFINITE_DISTANCE
#define INFINITE_DISTANCE INT_MAX
#define NOT_A_NODE -1
#endif
typedef struct arch_handler_s * arch_handler;
typedef struct dijkstra_s * dijkstra_t;

struct dijkstra_s {
    graph G;
    int size;
    int *father;
    float *distance;
    float (*peso)(void *);
};

struct arch_handler_s{
    int from;
    int to;
    void * formNodeInfo;
    void * archInfo;
    void * toNodeInfo;
};

dijkstra_t dijkstraInit(graph G,float (*peso)(void *));

dijkstra_t dijkstraRun(dijkstra_t d, int source);

// use codaGetNum to get direct the path
coda  dijkstraGetPathTo(dijkstra_t d,int node);
float dijkstraGetDistanceTo(dijkstra_t d,int dest);

void dijkstraSelfTest(void);

// float (*peso)(void *); must be an arch handler

#endif

/* exaple of peso
 
 float peso(void * pt){
    arch_handler a = pt; //cast to arch_handler 
    void  * archInfo = a->archInfo;   //get the inserted info
 
    float peso= *((float *)archInfo); //use the info
    return peso;
 };
 
 */
