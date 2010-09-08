//  coda.h   librerie-APA-2010


typedef struct coda_s *coda;

coda codaInit(void);
void codaPush(coda , void * elemento);
void * codaGet(coda);