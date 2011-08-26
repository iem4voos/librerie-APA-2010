Collezione Librerie Semplici in C
======================

Done
---------------

* [coda](http://it.wikipedia.org/wiki/Coda_%28informatica%29)
* matrici
* str2Int
* UnionFind

Todo
-----

* stack
* heap
* grafo

* algoritmi sui grafi


altro
.....

---
### matrici.h ###

 Questa libreria permette di creare e liberare la memoria 
 per matrici quadrate e cubiche

 uso:
 
        float **mat_2d=(float **)initMatt2d( 25, 3, float);
        float ***mat_3d=(float ***)initMatt3d(7, 9, 5, float);

        mat_2d[x][y]=z;
        mat_3d[j][k]=l;
        
        freeMat2d( mat_2d ,25,3);
        freeMat3d( mat_3d ,7, 9, 5);



---
### coda.h ###
Questa Libreria permette di gestire code e stack in particolare implementa funzioni per

	Push-->
    	+-+-+-+-+-+
    	| | | | | |
    	+-+-+-+-+-+
	<--Pop         Get-->


1. generiche
	- **init** : inizializza una nuova coda
	- **Free** : libera la memoria e cancella la coda
	- **Count** : conta gli elementi
	- **isEmpty** : controlla le la coda e vuota
+ inserimento
	- **Push** : inserimento in cima alla coda
	- **PushUniq** : inserisce un elemento che non sia già resente
+ estrazioone
	- **Pop** : estrazione dell'ultimo elemento inserito
	- **Get** : estrazione dell'elemento in cima
+ cancellazione
	- **codaDelByCompare** : cancella un elemento mediante confronto
+ scorrimento
	- **IteratorInit** : crea un elementoo che e possibile usare per scorrere la lista elemento per elemento
	- **Next**(Prev) : permette di accedere all'elemento sucessivo(precedente)
	- **IteratorRewind** : ri-posiziona l'"Itarator" all'inizio o alla fine della lista.

La libreria è orientata al lavoro con i puntatori, ma può essere usata anche con i numeri 

Esempio scorrimento

	coda C;
	C = codaInitNumeric();
	for (int i=0; i<5; i++) 
	        codaPushNum(C, i);
	
	I=codaIteratorInit(C, NULL, FORWARD_ITERATION);

	while ( (x=coda_NextNum(I))!=CODA_ITERATION_END ) 
			        printf(">%d\n",(int)x);

	codaIteratorFree(I);
	codaFree(C);
	
codaIteratorInit tiene  conto solo dello stato della coda al momento dell uso quindi va messo subito prima di ogni ciclo e comunque lontano da inerimenti e cancellazioni

--- 
	coda codaInit(void);
	void codaFree(coda);
	
	int codaCount(coda);
	int codaIsEmpty(coda C);
	
	void codaPush(coda , void * elemento);
	void codaPushUnique(coda , void *elem, int (*compare)(void *, void *));
	void * codaGet(coda);
	void * codaPop(coda);
	void * codaDelByCompare(coda , void * elem, int (*compare)(void *, void *));
	
	coda_iterator codaIteratorInit(coda C, void * element, enum iteration_direction);
	void codaIteratorFree(coda_iterator I);
	void * coda_Next(coda_iterator I);
	void * coda_Prev(coda_iterator I);
	
	/*----- NUMERIC VARIANTS-------*/
	coda codaInitNumeric(void); 	 // must be freed by codaFree(coda)
	
	void codaPushNum(coda C, float num);
	float codaPopNum(coda C);
	float codaGetNum(coda c);
	float codaDelNum(coda , float);
	
	float coda_NextNum(coda_iterator I);
	float coda_PrevNum(coda_iterator I);
	
---

### Graph.h ###

Permette di creare un grafo pesato o non sul quale e possibile eseguire operazioni elementari.

1. generiche
	+ **Init** : predispone la struttura per momorizzare un certo numero di nodi (che aumenta automaticamente se serve), si dichiara se il grafo è pesato o meno o orientato
+ sui nodi
	+ **CountEdges** : conta i nodi
	+ **GetEdges** : restituisce un vettore con tutti i nodi
	+ ****
+ sui archi
	+ **AddArch** : aggiunge un arco tra due nodi con la possibilita di aggiungere un puntatore con le informazioni come peso o altro
	+ **DelArch** : cancella un arco
	+ **GetArchsFrom** : restituisce un vettore con i nodi raggiungibili da un certo nodo

---

	graph graphInit(int nEdges, is_graph_oriented , is_graph_weithed);
	int   graphAddEdge(graph, int edge, void *edgeInfo);
	void  graphDelEdge(graph G, int edge);

	int  graphAddArch(graph G, int fromEdge, int toEdge, void *archInfo);
	void  graphDelArch(graph G, int fromEdge, int toEdge);


	int graphCountEdges(graph G);
	int * graphGetEdges(graph);
	int * graphGetArchsFrom(graph, int Edge);

---

### heap.h ###
permette di creare e di usare un heap. gli elementi gestiti sono puntatori il cui "valore"(proprità) è data dalla funzione passata durante l'inizializzazione


---

	heap heapInit(int size,int (*keyOfElement )(void *));
	void heapInsert(heap H, void * element);
	void * heapExtractMax(heap H);

---
###### note ######
[markdown tutorial](http://daringfireball.net/projects/markdown/dingus)

[fast git tutorial](librerie-APA-2010/Docs/fast_git_tutorial.html) from [http://book.git-scm.com/3_distributed_workflows.html](http://book.git-scm.com/3_distributed_workflows.html)

