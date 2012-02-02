//
//  heap.h
//  MicLibApa2010
//
//  Created by mic on 25/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef MicLibApa2010_heap_h
#define MicLibApa2010_heap_h

typedef struct heap_bin_s * heap ;

typedef enum heap_get_what_e{
    HEAP_GET_MAX,
    HEAP_GET_MIN
} heap_get_what;

heap heapInit(int size,float (*keyOfElement )(void *),heap_get_what);
void heapInsert(heap H, void * element);
void * heapExtract(heap H);

void heapRebuild(heap H);  //if content of ponters changhe update the heap

void heapSelfTest(void);

/* missing: 
 change proority
 - delete
 */

#endif
