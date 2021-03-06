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
#define MINUS_INFINITE_DISTANCE INT_MIN
#define NOT_A_NODE -1
#endif

typedef enum{SERCH_MIN,SERCH_MAX} kind_of_sech;

typedef struct dijkstra_s * dijkstra_t;

struct dijkstra_s {
    graph G;
    int size;
    int *father;
    float *distance;
    float (*peso)(void *);
    kind_of_sech kindOfSerch;
};

dijkstra_t dijkstraInit(graph G,float (*peso)(void *), kind_of_sech);

dijkstra_t dijkstraRun(dijkstra_t d, int source);

// use codaGetNum to get direct the path
coda  dijkstraGetPathTo(dijkstra_t d,int node);
float dijkstraGetDistanceTo(dijkstra_t d,int dest);

void dijkstraSelfTest(void);

// float (*peso)(void *); must be an arch handler as in graph.h

#endif


