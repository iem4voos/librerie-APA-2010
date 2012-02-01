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
    int nNodes;  // effectiv number of nodes
    int nArchs;  
    int maxNodes; // number if adj cells - size of the structure
    is_graph_oriented isGraphOriented;
    int (*compare_arch)(void *, void *);
    //coda C;
};

typedef enum{FROM,TO} from_or_to;
typedef enum{TRANSPOSE,COPY} transope_or_copy;

//MARK: - local functions prototypes
static graph graphCopyOrTranspose(graph ,transope_or_copy);
static int graph_checkSizeOrGrow(graph G, int nodeNum);
static int graph_arch_compare_default(void *, void *);
static int * graphGetArchsFromNodeX(graph , int, from_or_to  );
static int graphAddArch_X(graph , int, int, void *);

//MARK: - Functions

int graph_arch_compare_default(void *a, void *b){
    struct arch_s *A, *B;
    A = (struct arch_s *)a;
    B= (struct arch_s *)b;
    
    if (A->fromNode == B->fromNode && A->toNode == B->toNode) {
        return 0;
    }
    return 1;
}

void graphSetCompare(graph G, int (*compare)(void *,void *)){
    if (compare==NULL) {
        G->compare_arch=graph_arch_compare_default;
    }
    G->compare_arch=compare;
}

//MARK: - Init and Free

graph graphInit(int maxNodes, is_graph_oriented  isOriented){
    
    /*
    if (maxNodes==0) {
        maxNodes=GRAPH_DEFAULT_SIZE;
    }
     */
    
    graph G;
    G=malloc(sizeof(struct graph_s));
    puts("graph allocated");
    G->isGraphOriented=isOriented;
    G->nNodes   =G->nArchs=0;
    G->maxNodes =maxNodes;
    G->adj      =calloc(maxNodes, sizeof(struct node_s *));
    G->compare_arch=graph_arch_compare_default;
    
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

int graph_checkSizeOrGrow(graph G, int nodeNum){
    int newNodeNum;
    //puts("chaking the size of graph");
    
    if (nodeNum < G->maxNodes) {return 1;}
    
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
    for (int i=G->maxNodes; i< newNodeNum; G->adj[i++]=NULL);  
    G->maxNodes= newNodeNum;
    return 0;
}

//MARK: - Copy and Transpose

graph graphCopy(graph G){
    return graphCopyOrTranspose( G,COPY);
}
graph graphTranspose(graph G){
    return graphCopyOrTranspose( G,TRANSPOSE);
}

static graph graphCopyOrTranspose(graph G,transope_or_copy isToCopy){
    
    coda C;
    graph G2=graphInit(G->nNodes, G->isGraphOriented);
    struct arch_s * arc;
    
    // copy all nodes
    for (int i=0; i<G->maxNodes; i++) {
        if (G->adj[i]==NULL)continue;
        graphAddNode(G2, i, G->adj[i]->user_info);
    }
    
    //copy all arcs
    for (int i=0; i<G->maxNodes; i++) {
        if (G->adj[i]==NULL)continue;
        
        C=G->adj[i]->outgoing_arcs;
        coda_iterator I= codaIteratorInit(C, NULL, FORWARD_ITERATION);
        
        for (int i=0; (arc=coda_Next(I)); i++){
            if (isToCopy==COPY) {
                graphAddArch(G2, arc->fromNode, arc->toNode, arc->user_info);
            }else{ // from and to are swapped
                graphAddArch(G2, arc->toNode, arc->fromNode, arc->user_info);
            }
        }
        codaIteratorFree(I);
    }
    return G2;
}

//MARK: - Nodes

int graphAddNode(graph G, int nodeNum,    void *nodeInfo){
    struct node_s *Node;
    graph_checkSizeOrGrow(G,nodeNum);
    
    printf("adding che node num %d\n", nodeNum);
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

void * graphGetNodeData(graph G, int nodeNum){
    return G->adj[nodeNum]->user_info;
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

//MARK: - Archs

int  graphAddArch(graph G, int fromNode,   int toNode, void *archInfo){
    
    if (G->adj[fromNode] == NULL || G->adj[toNode] == NULL) {
        
        
        if (G->adj[fromNode] == NULL) {
            printf("\n the node %d dont exist\n", fromNode);
        }
        if(G->adj[toNode] == NULL){
            printf("\n the node %d dont exist\n", toNode);
        }
        
        return EXIT_FAILURE;
    }
    
    graphAddArch_X(G, fromNode, toNode, archInfo);
    
    if ( G->isGraphOriented == GRAPH_IS_NOT_ORIENTED) {
        graphAddArch_X(G, toNode, fromNode, archInfo); 
    }
    return EXIT_SUCCESS;
}

//#warning graph_arch_compare
int  graphAddArch_X(graph G, int fromNode,   int toNode, void *archInfo){
    struct arch_s * a;
    
    printf("adding arch [%d]->[%d]\n", fromNode, toNode);
    
    graph_checkSizeOrGrow(G,fromNode);
    graph_checkSizeOrGrow(G,toNode);
    
    a=malloc(sizeof(struct arch_s));
    a->fromNode=fromNode;
    a->toNode=toNode;
    a->user_info=archInfo;
    codaPushUnique(G->adj[fromNode]->outgoing_arcs, a, G->compare_arch);
    
    // to edge indicate incoming arch- is only a pounter do not free
    codaPushUnique(G->adj[toNode]->incoming_arcs, a, G->compare_arch);
    
    G->nArchs++;
    return EXIT_SUCCESS;
}


//#warning graph_arch_compare
void  graphDelArch(graph G, int fromNode, int toNode){
    //
    coda arches;//, delended;
    struct arch_s arch, *delended;;
    
    arch.fromNode=fromNode;
    arch.toNode=toNode;
    
    
    arches=G->adj[toNode]->incoming_arcs;
    codaDelByCompare(arches, &arch, G->compare_arch);
    
    arches=G->adj[fromNode]->outgoing_arcs;
    delended=codaDelByCompare(arches, &arch, G->compare_arch);
    free(delended); // only this must be freed incoming are only pointers

    if (G->isGraphOriented == GRAPH_IS_NOT_ORIENTED) {
        
        int tmp;  // swap origin and destination
        tmp=toNode; toNode=fromNode; fromNode=tmp;
        
        arch.fromNode=fromNode;
        arch.toNode=toNode;
        
        arches=G->adj[toNode]->incoming_arcs;
        codaDelByCompare(arches, &arch, G->compare_arch);
        
        arches=G->adj[fromNode]->outgoing_arcs;
        delended=codaDelByCompare(arches, &arch, G->compare_arch);
        free(delended); // only this must be freed incoming are only pointers
        
    }
}



void * graphGetArchData(graph G, int from, int to){
    struct arch_s arch, *serchedArch;
    arch.fromNode = from;
    arch.toNode   = to;
    serchedArch = codaSerch( G->adj[from]->outgoing_arcs , &arch, G->compare_arch);
    return serchedArch->user_info;
}

//MARK: get archs

// return NULL in case of Empty
int * graphGetArchsToNode(graph G, int node){
    return graphGetArchsFromNodeX(G, node, TO );
}
int * graphGetArchsFromNode(graph G, int Node){
    return graphGetArchsFromNodeX(G, Node, FROM );
}

int * graphGetArchsFromNodeX(graph G, int Node, from_or_to isFrom )
{
    coda C;
    coda_iterator I;
    struct arch_s *arc;
    int *vett,num_archi;
    
    // aggiunto secodo criterio - testare
    if (G->maxNodes < Node || G->adj[Node] == NULL) {
        puts("errore interno graphGetArchsFromNode");
        printf("Node: %d , G->nNodes= %d\n", Node, G->nNodes);
        return NULL;
    }
    
    if (isFrom== FROM)
        C=G->adj[Node]->outgoing_arcs;
    else
        C=G->adj[Node]->incoming_arcs;
    
    num_archi=codaCount(C);
    
    if (num_archi==0) {return NULL;}
    
    I= codaIteratorInit(C, NULL, FORWARD_ITERATION);
    vett=calloc(num_archi, sizeof(int));
    
    for (int i=0; (arc=coda_Next(I)); i++)
        vett[i]=arc->toNode;
    
    codaIteratorFree(I);
    return vett;
}



//MARK: - Count

int graphGetMaxNodes(graph G){
    return G->maxNodes;
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

graph graph_selftest1(void){
    graph G;
    
    puts("graph selftest");
    
    G=graphInit(10, GRAPH_IS_NOT_ORIENTED);
    
    for (int i=1; i<6; i++) {
        graphAddNode(G, i, NULL);
    }

    graphAddNode(G, 10, NULL);
    
    for (int i=1; i<6; i+=1)
    {
        graphAddArch(G, 1, i, NULL);
    }
    
    
    graphAddArch(G, 2, 1, NULL);
    graphAddArch(G, 10, 3, NULL);
    
    graphDelArch(G, 1, 2);
    
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
