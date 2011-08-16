//  coda.h   librerie-APA-2010

#define DEBUG 1

typedef struct coda_s *coda;

/*
 Push-->
     +-+-+-+-+-+
     | | | | | |
     +-+-+-+-+-+
 <--Pop         Get-->
 
 */

//void codaAppend(coda , void * elemento);

coda codaInit(void);
void codaPush(coda , void * elemento);
void * codaGet(coda);
void * codaPop(coda);
void codaFree(coda);

int codaCount(coda);
int codaIsEmpty(coda C);

coda codaInitNumeric(void);
void codaPushNum(coda C, float num);
float codaPopNum(coda C);
float codaGetNum(coda c);
