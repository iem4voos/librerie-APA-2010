Collezione Librerie Semplici in C
======================

Done
---------------

* [coda](http://it.wikipedia.org/wiki/Coda_%28informatica%29)
* matrici

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
	- **Next**(Prev) : permette di accedere all'elemento sucessivo(precedente)

La libreria è orientata al lavoro con i puntatori, ma può essere usata anche con i numeri 

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



---
###### note ######
[markdown tutorial](http://daringfireball.net/projects/markdown/dingus)

[fast git tutorial](librerie-APA-2010/Docs/fast_git_tutorial.html) from [http://book.git-scm.com/3_distributed_workflows.html](http://book.git-scm.com/3_distributed_workflows.html)

