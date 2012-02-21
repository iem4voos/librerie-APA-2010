//
//  dijkstra.c
//  MicLibApa2010
//
//  Created by mic on 3/01/12.

#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "heap.h"



dijkstra_t dijkstraInit(graph G,float (*peso)(void *), kind_of_sech kindOfSerch){
    dijkstra_t d;
    int nNodes;
    
    d=malloc(sizeof(struct dijkstra_s));
    nNodes= graphGetMaxNodes(G);
    
    d->size=nNodes;
    d->G=G;
    d->father   = calloc(nNodes, sizeof(int));
    d->distance = calloc(nNodes, sizeof(int));
    d->peso=peso;
    d->kindOfSerch=kindOfSerch;
    
    for (int i=0; i<nNodes; i++) {
        d->father[i]  = NOT_A_NODE;
        if (kindOfSerch==SERCH_MIN) {
            d->distance[i]= INFINITE_DISTANCE;
        }else{
            d->distance[i]= MINUS_INFINITE_DISTANCE;
        }
        
    }
    
    return d;
}

void dijkstraFree(dijkstra_t d){
    free(d->father);
    free(d->distance);
    free(d);
}

static void relax(dijkstra_t d, int from, int to){
    
    float distanza;
    struct arch_handler_s ah;
    
    ah.from=from;
    ah.to=to;
    ah.formNodeInfo = graphGetNodeData(d->G, from);
    ah.toNodeInfo   = graphGetNodeData(d->G, to);
    ah.archInfo     = graphGetArchData(d->G, from, to);

    distanza= d->distance[from] + d->peso(&ah);
#warning complete the min max...    
    if (d->distance[to] > distanza ) {
        d->distance[to] = distanza;
        d->father[to]   = from;
    }
}

static float keyOfFloatPt(void *elem){
    float *x,num;
    x=elem;
    if (elem==NULL) {return 0;}
    num=*x;
    
    return num;
}

heap populateHeap(dijkstra_t d){
    heap h;
    int nodes=graphGetMaxNodes(d->G);
    
    if (d->kindOfSerch==SERCH_MIN) {
        h=heapInit(nodes, keyOfFloatPt, HEAP_GET_MIN);
    }else{
        h=heapInit(nodes, keyOfFloatPt, HEAP_GET_MAX);
    }
    
    for (int i=0; i<nodes; i++) {
        printf("popolo %d con %f\n", i,d->distance[i]  );
        heapInsert(h, &(d->distance[i]));
    }
    
    return h;
}

dijkstra_t dijkstraRun(dijkstra_t d, int source){
    heap h;
    void * ptr,*ref=&(d->distance[0]);  // distance is a float    
    int nodeNum, *adj, adjCount;
    
    d->distance[source]=0;
    
    h=populateHeap(d);
    
    
    while ((ptr=heapExtract(h))!=NULL) {
        nodeNum= (int)(ptr-ref)/sizeof(float);  // crazy pointers hack
        
        adjCount = graphCountArchsFromNode(d->G, nodeNum);
        adj      = graphGetArchsFromNode(d->G, nodeNum);
        
        if (adjCount==0) {
            continue;
        }
        
        for (int i=0; i<adjCount; i++) {
            relax(d, nodeNum, adj[i]);
        }
        heapRebuild(h);
    }    
    return d;
}

float dijkstraGetDistanceTo(dijkstra_t d,int a){
    return d->distance[a];
}

coda dijkstraGetPathTo(dijkstra_t d,int node){
    int prev;
    coda C=codaInitNumeric();
    
    codaPushNum(C, node);
    
    while ((prev=d->father[node])!=NOT_A_NODE) {
        codaPushNum(C, prev);
        node=prev;
    }
    return C;
}


void dijkstraPrint(dijkstra_t d){
    
    int nNodes = d->size;
    
    puts("\n ---- Distances ----");
    for (int i=0; i< nNodes; i++) {
        printf(" %2.1f |", (d->distance[i]==INFINITE_DISTANCE)? -1.0 : d->distance[i]  );
    }
    
    puts("\n ---- Fathers ----");
    for (int i=0; i< nNodes; i++) {
        printf(" %2.0f |", (d->father[i]==NOT_A_NODE)? -1.0 : d->father[i]  );
    }


}

//MARK: - SELFTEST -
float peso(void * pt){
    arch_handler a=pt;
    void * archInfo;
    
    archInfo= a->archInfo;
    float peso= *((float *)archInfo);
    return peso;
};

void dijkstraSelfTest(void){
    
    graph g;
    
    float pesi[8]={1,1,1,2,2,2,2,2};
    
    g=graphInit(6, GRAPH_IS_ORIENTED);
    for (int i=1; i<7; i++) {
        graphAddNode(g, i, NULL);
    }
    
    graphAddArch(g, 1, 2, &pesi[0]);
    graphAddArch(g, 2, 5, &pesi[0]);
    graphAddArch(g, 5, 6, &pesi[0]);
    
    graphAddArch(g, 1, 3, &pesi[4]);
    graphAddArch(g, 2, 4, &pesi[4]);
    graphAddArch(g, 4, 6, &pesi[4]);
    
    graphAddArch(g, 3, 5, &pesi[4]);
    graphAddArch(g, 3, 4, &pesi[4]);
    
    
    dijkstra_t d=dijkstraInit(g, peso, SERCH_MIN);
    d=dijkstraRun(d, 1);
    
    dijkstraPrint( d);
    
    coda c=dijkstraGetPathTo(d,6);
    
    //oda_iterator I=codaIteratorInit(c, NULL, BACKWARD_ITERATION);
    

    while (codaIsEmpty(c)==0) {
        printf("%.0f->", codaGetNum(c));
    }
    
    printf("\ndistanza: %.0f", dijkstraGetDistanceTo(d, 6));
    
    
    dijkstraFree(d);
    
    printf("marmotta");

}








