//
//  graph.c
//  MicLibApa2010
//
//  Created by mic on 21/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

//#ifdef Mic_graph_USE_ADJ_LIST

#include <stdio.h>
#include "graph.h"
#include "coda.h"

#define GRAPH_DEFAULT_SIZE 100;

// local functions
int graph_checkSizeOrGrow(graph G, int edgeNum);
int arch_compare(void *, void *);

struct edge_s {
    int num;
    coda adj_from;
    coda adj_to;
    void * user_info;
};

struct arch_s {
    int edgeNum;
    int fromEdge;
    int toEdge;
    void * user_info;
};

struct graph_s {
    struct edge_s **adj;
    int nEdges;
    int nArchs;
    int maxEdges;
    int isGraphOriented;
    //coda C;
};

int arch_compare(void * a, void * b){
    
    struct arch_s *A, *B;
    A=(struct arch_s *) a;
    B=(struct arch_s *) b;
    
    if (A->fromEdge == B->fromEdge && A->toEdge == B->toEdge) {
        return 0;
    }
    
    return 1;
}

graph graphInit(int nEdges, int isOriented, int isWeithed){
    graph G;
    G=malloc(sizeof(struct graph_s));
    puts("graph allocated");
    G->isGraphOriented=isOriented;
    G->nEdges   =G->nArchs=0;
    G->maxEdges =nEdges;
    G->adj      =calloc(nEdges, sizeof(struct edge_s *));
    puts("allocated the vector of edges");
    for (int i=0; i<nEdges; G->adj[i++]=NULL); //initialize adj to null
    puts("edges initialized to null");
    return G;
}

int graph_checkSizeOrGrow(graph G, int edgeNum){
    int newEdgeNum;
    //puts("chaking the size of graph");
    
    if (edgeNum < G->maxEdges)
    {
        //puts("size is ok");
        return 1;
    }
    
    newEdgeNum= (int)(edgeNum * 1.5);
    G->adj=realloc(G->adj, sizeof(struct edge_s *) *  newEdgeNum );
    if (!G->adj) { 
        puts("reallocation Failed!! Exit!!");
        exit(EXIT_FAILURE);
    }else{ 
        printf("increased the size (from %d to %d) to fit new edges\n",G->maxEdges, newEdgeNum );
    }
    // initalize the new allocated cells
    for (int i=edgeNum; i< newEdgeNum; G->adj[i++]=NULL);  
    G->maxEdges= newEdgeNum;
    return 0;
}

int graphAddEdge(graph G, int edgeNum,    void *edgeInfo){
    struct edge_s *E;
    graph_checkSizeOrGrow(G,edgeNum);
    
    printf("\nadding che edge num %d", edgeNum);
    if (G->adj[edgeNum]!=NULL)
    {
        puts("edge already exists");
        return 1;
    }
    
    E=malloc(sizeof(struct edge_s));
    E->num=edgeNum;
    E->user_info=edgeInfo;
    E->adj_from=codaInit();
    E->adj_to=codaInit();
    //puts("edge created");
    
    G->adj[edgeNum]=E;
    //puts("edge added to G->adj[]");
    
    G->nEdges++;
    
    return 0;
}


void  graphDelEdge(graph G, int edge){
    codaFree(G->adj[edge]->adj_from);
    codaFree(G->adj[edge]->adj_to);
    //free(G->adj[edge]);
    G->adj[edge]=NULL;
}

#warning "da fare"

void  graphDelArch(graph G, int fromEdge, int toEdge){
    //
    coda tmpC;
    tmpC=codaInit();
    struct arch_s *a;
    
    while ((a = codaGet(G->adj[fromEdge]->adj_to)))
        if (a->toEdge == toEdge && a->fromEdge == fromEdge)
            G->nEdges--;
        else
            codaPush(tmpC, a); // push it back
    G->adj[fromEdge]->adj_to=tmpC;
    codaFree(tmpC);
    tmpC=codaInit();
    while ((a = codaGet(G->adj[toEdge]->adj_from)))
        if (a->toEdge == toEdge && a->fromEdge == fromEdge)
            G->nEdges--;
        else
            codaPush(tmpC, a); // push it back
    G->adj[fromEdge]->adj_from=tmpC;
    free(a);
}


void  graphAddArch(graph G, int fromEdge,   int toEdge, void *archInfo){
    struct arch_s * a;
    
    //printf("adding arch %d-%d", fromEdge, toEdge);
    a=malloc(sizeof(struct arch_s));
    a->fromEdge=fromEdge;
    a->toEdge=toEdge;
    a->user_info=archInfo;
    //puts("arch created");
    
    graph_checkSizeOrGrow(G,fromEdge);
    graph_checkSizeOrGrow(G,toEdge);
    
    //puts("pushing the edge to G->adj[]->X");
    codaPushUnique(G->adj[fromEdge]->adj_to,   a, arch_compare);
    codaPushUnique(G->adj[toEdge]  ->adj_from, a, arch_compare);
    
    if (!G->isGraphOriented) {
        a=malloc(sizeof(struct arch_s));
        a->fromEdge=toEdge;  // invertiti
        a->toEdge=fromEdge;
        a->user_info=archInfo;
        
        codaPushUnique(G->adj[toEdge]  ->adj_to,   a,arch_compare);
        codaPushUnique(G->adj[fromEdge]->adj_from, a,arch_compare);
    }
    
    G->nArchs++;
    
}

int graphCountEdges(graph G){
    return G->nEdges;
}

int graphCountArchsFromEdge(graph G, int edge){
    return codaCount( G->adj[edge]->adj_to);
}

int graphCountArchsToEdge(graph G, int edge){
    return codaCount( G->adj[edge]->adj_from);
}

int * graphGetEdges(graph G){
    //struct edge_s * E;
    int *vet;
    int j=0;
    
    vet= calloc(G->nEdges, sizeof(int));
    
    for (int i=0; i< G->maxEdges; i++) {
        if (G->adj[i]!=NULL) {
            vet[j]=i;
            j++;
        } 
    }
    return vet;
}

#warning pacco
int * graphGetArchsFrom(graph G, int Edge){
    coda C=G->adj[Edge]->adj_to;
    coda_iterator I;
    struct arch_s *arc;
    int *vett;
    int i=0;
        
    vett=calloc(codaCount(C), sizeof(int));
    printf("\n allocato vettore %d elem", codaCount(C));
    
    I= codaIteratorInit(C, NULL, FORWARD_ITERATION);
    
    
    while ((arc=coda_Next(I))) {
        vett[i]=arc->toEdge;
        i++;
    }
    codaIteratorFree(I);
    return vett;
}

void graph_selftest1(void){
    graph G;
    
    puts("graph selftest");
    
    G=graphInit(10, 1, 1);
    
    graphAddEdge(G, 3, NULL);
    graphAddEdge(G, 1, NULL);
    graphAddEdge(G, 5, NULL);
    graphAddEdge(G, 2, NULL);
    
    graphAddArch(G, 1, 5, NULL);
    graphAddArch(G, 1, 1, NULL);
    graphAddArch(G, 1, 3, NULL);
    
    puts("rimuovo arco 1 5");
    graphDelArch(G, 1, 5);
    
    int *vett= graphGetEdges(G);
    int *archi;
    
    printf("numero di nodi: %d", graphCountEdges(G));
    
    for (int i=0; i< graphCountEdges(G); i++) {
        printf("\n nodo:> %d", vett[i]);
        archi= graphGetArchsFrom(G, vett[i]);
        for (int j=0; j< graphCountArchsFromEdge(G, vett[i]); j++) {
            printf("--> %d ,", archi[j]);
        }
    }
    
    puts("graph selftest END");
    
}

//#endif
