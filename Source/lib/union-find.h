//
//  union-find.h
//  MicLibApa2010
//
//  Created by mic on 16/08/11.
//

#ifndef MicLibApa2010_union_find_h
#define MicLibApa2010_union_find_h

typedef struct uf_handler_s * uf_handler;

//void selftest1(void);

void uf_selftest(void);

uf_handler uf_init     (int max_len);
void         uf_free     (uf_handler H);

// find if two numbers are connected
int          uf_find     (uf_handler H, int p, int q);

// union two numbers
int          uf_unionFind(uf_handler H, int p, int q);

int uf_size(uf_handler H);

#endif
