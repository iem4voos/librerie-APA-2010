//  coda.h   librerie-APA-2010

#define DEBUG 1

typedef struct coda_s *coda;

coda codaInit(void);
void codaAppend(coda , void * elemento);
void * codaGet(coda);