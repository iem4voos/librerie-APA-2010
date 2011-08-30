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
    coda incoming_arcs;
    coda outgoing_arcs;
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
    is_graph_oriented isGraphOriented;
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

graph graphInit(int maxEdges, is_graph_oriented  isOriented, is_graph_weithed isWeithed){
    graph G;
    G=malloc(sizeof(struct graph_s));
    puts("graph allocated");
    G->isGraphOriented=isOriented;
    G->nEdges   =G->nArchs=0;
    G->maxEdges =maxEdges;
    G->adj      =calloc(maxEdges, sizeof(struct edge_s *));
    puts("allocated the vector of edges");
    for (int i=0; i<maxEdges; G->adj[i++]=NULL); //initialize adj to null
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
    E->incoming_arcs=codaInit();
    E->outgoing_arcs=codaInit();
    //puts("edge created");
    
    G->adj[edgeNum]=E;
    //puts("edge added to G->adj[]");
    
    G->nEdges++;
    
    return 0;
}


void  graphDelEdge(graph G, int edge){
    codaFree(G->adj[edge]->incoming_arcs);
    codaFree(G->adj[edge]->outgoing_arcs);
    //free(G->adj[edge]);
    G->adj[edge]=NULL;
}



int graph_arch_compare(void *a, void *b){
    struct arch_s *uno, *due;
    uno = (struct arch_s *)a;
    due= (struct arch_s *)b;
    
    if (uno->fromEdge == due->fromEdge && uno->toEdge == due->toEdge) {
        return 0;
    }
    return 1;
}
#warning "controllare : la parte non orientata non va!!

void  graphDelArch(graph G, int fromEdge, int toEdge){
    //
    coda arches;
    struct arch_s a;
    
    a.fromEdge=fromEdge;
    a.toEdge=toEdge;
    
    arches=G->adj[fromEdge]->outgoing_arcs;
    codaDelByCompare(arches, &a, graph_arch_compare);
    
    arches=G->adj[toEdge]->incoming_arcs;
    codaDelByCompare(arches, &a, graph_arch_compare);
    
    if (G->isGraphOriented == GRAPH_IS_NOT_ORIENTED) {
        a.fromEdge=toEdge;  // sono inveriti
        a.toEdge=fromEdge;
        
        arches=G->adj[toEdge]->outgoing_arcs;
        codaDelByCompare(arches, &a, graph_arch_compare);
        
        arches=G->adj[fromEdge]->incoming_arcs;
        codaDelByCompare(arches, &a, graph_arch_compare);
    }
    
}

int  graphAddArch_X(graph G, int fromEdge,   int toEdge, void *archInfo){
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
    codaPushUnique(G->adj[fromEdge]->outgoing_arcs, a, arch_compare);
    codaPushUnique(G->adj[toEdge]  ->incoming_arcs, a, arch_compare);
    
    G->nArchs++;
    
    return EXIT_SUCCESS;
}

int  graphAddArch(graph G, int fromEdge,   int toEdge, void *archInfo){
    //struct arch_s * a;
    
    if (G->adj[fromEdge] == NULL || G->adj[toEdge] == NULL) {
        puts("\nthe node du not exist");
        return EXIT_FAILURE;
    }
    
    graphAddArch_X(G, fromEdge, toEdge, archInfo);
    
    if ( G->isGraphOriented == GRAPH_IS_NOT_ORIENTED) {
       graphAddArch_X(G, toEdge, fromEdge, archInfo); 
    }
    
    return EXIT_SUCCESS;
}

int graphCountEdges(graph G){
    return G->nEdges;
}

int graphCountArchsFromEdge(graph G, int edge){
    if (G->adj[edge] == NULL) 
        return 0;
    
    return codaCount( G->adj[edge]->outgoing_arcs);   
}

int graphCountArchsToEdge(graph G, int edge){
    return codaCount( G->adj[edge]->incoming_arcs);
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

#warning pacco ?? se si perche? perche nel caso ce ne sia solo uno da zero e non il num
// return NULL in case of Empty
int * graphGetArchsFromEdge(graph G, int Edge)
{
    coda C;
    coda_iterator I;
    struct arch_s *arc;
    int *vett,num_archi;
    
    // aggiunto secodo criterio - testare
    if (G->nEdges < Edge || G->adj[Edge] == NULL) {
        return NULL;
    }
    
    C=G->adj[Edge]->outgoing_arcs;
    num_archi=codaCount(C);
    
    if (num_archi==0) {
        return NULL;
    }
        
    vett=calloc(num_archi, sizeof(int));
    //printf("\n graphGetArchsFromEdge:  allocato vettore %d elem", codaCount(C));
    
    I= codaIteratorInit(C, NULL, FORWARD_ITERATION);
    
    for (int i=0; (arc=coda_Next(I)); i++)
        vett[i]=arc->toEdge;


    codaIteratorFree(I);
    return vett;
}

graph graph_selftest1(void){
    graph G;
    
    puts("graph selftest");
    
    G=graphInit(10, GRAPH_IS_NOT_ORIENTED, GRAPH_IS_WEIGHTD);
    
    for (int i=1; i<6; i++) {
        graphAddEdge(G, i, NULL);
    }

    graphAddEdge(G, 10, NULL);
    
    for (int i=1; i<6; i+=1)
    {
        graphAddArch(G, 1, i, NULL);
    }
    
    graphAddArch(G, 10, 3, NULL);
    
    puts("\nrimuovo arco 1 5");
    graphDelArch(G, 1, 5);
    
    int *vett= graphGetEdges(G);
    int *archi;
    
    printf("\nnumero di nodi: %d\n", graphCountEdges(G));
    
    for (int i=0; i< graphCountEdges(G); i++) {
        
        printf("\n nodo:> %3d (%d) |", vett[i], graphCountArchsFromEdge(G, vett[i]));
        
        if ( (archi= graphGetArchsFromEdge(G, vett[i])) != NULL ){
            for (int j=0; j< graphCountArchsFromEdge(G, vett[i]); j++) {
                printf(" -->%3d", archi[j]);
            }
        }
    }
    
    puts("\ngraph selftest END");
    return G;
}

//#endif
