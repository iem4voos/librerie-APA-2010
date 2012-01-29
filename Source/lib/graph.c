//
//  graph.c
//  MicLibApa2010
//
//  Created by mic on 21/08/11.
//

//#ifdef Mic_graph_USE_ADJ_LIST

#include <stdio.h>
#include "graph.h"
#include "coda.h"

#define GRAPH_DEFAULT_SIZE 100;

struct node_s {
    int num;
    coda incoming_arcs;
    coda outgoing_arcs;
    void * user_info;
};

struct arch_s {
    int nodeNum;
    int fromNode;
    int toNode;
    void * user_info;
};

struct graph_s {
    struct node_s **adj;
    int nNodes;
    int nArchs;
    int maxNodes;
    is_graph_oriented isGraphOriented;
    //coda C;
};

//MARK: local functions prototypes
static int graph_checkSizeOrGrow(graph G, int nodeNum);
static int arch_compare(void *, void *);


//MARK: functions

graph graphInit(int maxNodes, is_graph_oriented  isOriented, is_graph_weithed isWeithed){
    graph G;
    G=malloc(sizeof(struct graph_s));
    puts("graph allocated");
    G->isGraphOriented=isOriented;
    G->nNodes   =G->nArchs=0;
    G->maxNodes =maxNodes;
    G->adj      =calloc(maxNodes, sizeof(struct node_s *));
    puts("allocated the vector of edges");
    for (int i=0; i<maxNodes; G->adj[i++]=NULL); //initialize adj to null
    puts("edges initialized to null");
    return G;
}

void graphFree(graph G){
    
    for (int i=G->maxNodes; i>=0; i--) {
        if (G->adj[i] && G->adj[i]->outgoing_arcs!=NULL) 
            codaFree(G->adj[i]->outgoing_arcs);
        free(G->adj[i]);
    }
    free(G->adj);
}

int graphAddNode(graph G, int nodeNum,    void *nodeInfo){
    struct node_s *Node;
    graph_checkSizeOrGrow(G,nodeNum);
    
    printf("\nadding che edge num %d", nodeNum);
    if (G->adj[nodeNum]!=NULL)
    {
        puts("node already exists");
        return 1;
    }
    
    Node=malloc(sizeof(struct node_s));
    Node->num=nodeNum;
    Node->user_info=nodeInfo;
    Node->incoming_arcs=codaInit();
    Node->outgoing_arcs=codaInit();
    
    G->adj[nodeNum]=Node;
    
    G->nNodes++;
    return 0;
}

void  graphDelNode(graph G, int node){
    codaFree(G->adj[node]->incoming_arcs);
    codaFreeWithContent(G->adj[node]->outgoing_arcs);
    //free(G->adj[node]); // this is an array!! what to free??
    G->adj[node]=NULL;
}

int graph_arch_compare(void *a, void *b){
    struct arch_s *uno, *due;
    uno = (struct arch_s *)a;
    due= (struct arch_s *)b;
    
    if (uno->fromNode == due->fromNode && uno->toNode == due->toNode) {
        return 0;
    }
    return 1;
}
#warning "controllare : la parte non orientata non va!!

void  graphDelArch(graph G, int fromNode, int toNode){
    //
    coda arches, delended;
    struct arch_s arch;
    
    arch.fromNode=fromNode;
    arch.toNode=toNode;
    
    
    arches=G->adj[toNode]->incoming_arcs;
    codaDelByCompare(arches, &arch, graph_arch_compare);
    
    arches=G->adj[fromNode]->outgoing_arcs;
    delended=codaDelByCompare(arches, &arch, graph_arch_compare);
    free(delended); // only this must be freed incoming are only pointers

    if (G->isGraphOriented == GRAPH_IS_NOT_ORIENTED) {
        
        int tmp;  // swap origin and destination
        tmp=toNode; toNode=fromNode; fromNode=tmp;
        
        arch.fromNode=fromNode;
        arch.toNode=toNode;
        
        arches=G->adj[toNode]->incoming_arcs;
        codaDelByCompare(arches, &arch, graph_arch_compare);
        
        arches=G->adj[fromNode]->outgoing_arcs;
        delended=codaDelByCompare(arches, &arch, graph_arch_compare);
        free(delended); // only this must be freed incoming are only pointers
        
    }
}

int  graphAddArch_X(graph G, int fromNode,   int toNode, void *archInfo){
    struct arch_s * a;
    
    printf("adding arch [%d]->[%d]\n", fromNode, toNode);
    
    graph_checkSizeOrGrow(G,fromNode);
    graph_checkSizeOrGrow(G,toNode);
    
    a=malloc(sizeof(struct arch_s));
    a->fromNode=fromNode;
    a->toNode=toNode;
    a->user_info=archInfo;
    codaPushUnique(G->adj[fromNode]->outgoing_arcs, a, arch_compare);
    
    // to edge indicate incoming arch- is only a pounter do not free
    codaPushUnique(G->adj[toNode]->incoming_arcs, a, arch_compare);

    G->nArchs++;
    return EXIT_SUCCESS;
}

int  graphAddArch(graph G, int fromNode,   int toNode, void *archInfo){
    //struct arch_s * a;
    
    
    if (G->adj[fromNode] == NULL || G->adj[toNode] == NULL) {
        puts("\nthe node du not exist");
        return EXIT_FAILURE;
    }
    
    
    
    graphAddArch_X(G, fromNode, toNode, archInfo);
    
    if ( G->isGraphOriented == GRAPH_IS_NOT_ORIENTED) {
       graphAddArch_X(G, toNode, fromNode, archInfo); 
    }
    return EXIT_SUCCESS;
}

int graphCountNodes(graph G){
    return G->nNodes;
}

int graphCountArchsFromNode(graph G, int edge){
    if (G->adj[edge] == NULL) 
        return 0;
    
    return codaCount( G->adj[edge]->outgoing_arcs);   
}

int graphCountArchsToNode(graph G, int edge){
    return codaCount( G->adj[edge]->incoming_arcs);
}

int * graphGetNodes(graph G){
    //struct edge_s * E;
    int *vet;
    int j=0;
    
    vet= calloc(G->nNodes, sizeof(int));
    
    for (int i=0; i< G->maxNodes; i++) {
        if (G->adj[i]!=NULL) {
            vet[j]=i;
            j++;
        } 
    }
    return vet;
}

#warning pacco ?? se si perche? perche nel caso ce ne sia solo uno da zero e non il num
// return NULL in case of Empty
int * graphGetArchsFromNode(graph G, int Node)
{
    coda C;
    coda_iterator I;
    struct arch_s *arc;
    int *vett,num_archi;
    
    // aggiunto secodo criterio - testare
    if (G->maxNodes < Node || G->adj[Node] == NULL) {
        puts("errore interno graphGetArchsFromNode");
        
        printf("Node: %d , G->nNodes= %d", Node, G->nNodes);
        
        return NULL;
    }
    
    C=G->adj[Node]->outgoing_arcs;
    num_archi=codaCount(C);
    
    if (num_archi==0) {
        return NULL;
    }
        
    vett=calloc(num_archi, sizeof(int));
    //printf("\n graphGetArchsFromEdge:  allocato vettore %d elem", codaCount(C));
    
    I= codaIteratorInit(C, NULL, FORWARD_ITERATION);
    
    for (int i=0; (arc=coda_Next(I)); i++)
        vett[i]=arc->toNode;

    codaIteratorFree(I);
    return vett;
}

int arch_compare(void * a, void * b){
    
    struct arch_s *A, *B;
    A=(struct arch_s *) a;
    B=(struct arch_s *) b;
    
    if (A->fromNode == B->fromNode && A->toNode == B->toNode) {
        return 0;
    }
    
    return 1;
}

int graph_checkSizeOrGrow(graph G, int nodeNum){
    int newNodeNum;
    //puts("chaking the size of graph");
    
    if (nodeNum < G->maxNodes)
    {
        //puts("size is ok");
        return 1;
    }
    
    newNodeNum= (int)(nodeNum * 1.5);
    G->adj=realloc(G->adj, sizeof(struct node_s *) *  newNodeNum );
    if (!G->adj) { 
        puts("reallocation Failed!! Exit!!");
        exit(EXIT_FAILURE);
    }else{ 
        printf("increased the size (from %d to %d) to fit \
               new edges\n",G->maxNodes, newNodeNum );
    }
    // initalize the new allocated cells
    for (int i=nodeNum; i< newNodeNum; G->adj[i++]=NULL);  
    G->maxNodes= newNodeNum;
    return 0;
}

graph graph_selftest1(void){
    graph G;
    
    puts("graph selftest");
    
    G=graphInit(10, GRAPH_IS_ORIENTED, GRAPH_IS_WEIGHTD);
    
    for (int i=1; i<6; i++) {
        graphAddNode(G, i, NULL);
    }

    graphAddNode(G, 10, NULL);
    
    for (int i=1; i<6; i+=1)
    {
        graphAddArch(G, 1, i, NULL);
    }
    
    graphAddArch(G, 10, 3, NULL);
    
    puts("\nrimuovo arco 1 5");
    graphDelArch(G, 1, 5);
    
    int *vett= graphGetNodes(G);
    int *archi;
    
    printf("\nnumero di nodi: %d\n", graphCountNodes(G));
    
    for (int i=0; i< graphCountNodes(G); i++) {
        
        printf("\n nodo:> %3d (%d) |", vett[i], graphCountArchsFromNode(G, vett[i]));
        
        if ( (archi= graphGetArchsFromNode(G, vett[i])) != NULL ){
            for (int j=0; j< graphCountArchsFromNode(G, vett[i]); j++) {
                printf(" -->%3d", archi[j]);
            }
        }
    }
    
    
    puts("\ngraph selftest END");
    return G;
}

//#endif
