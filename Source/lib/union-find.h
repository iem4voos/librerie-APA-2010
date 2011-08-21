//
//  union-find.h
//  MicLibApa2010
//
//  Created by mic on 16/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef MicLibApa2010_union_find_h
#define MicLibApa2010_union_find_h

typedef struct uf_handler_s * uf_handler_t;

//void selftest1(void);

void uf_selftest(void);

uf_handler_t uf_init     (int max_len);
void         uf_free     (uf_handler_t H);
int          uf_find     (uf_handler_t H, int p, int q);
int          uf_unionFind(uf_handler_t H, int p, int q);

#endif
