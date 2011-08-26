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

heap heapInit(int size,int (*keyOfElement )(void *));
void heapInsert(heap H, void * element);
void * heapExtractMax(heap H);

void heapSelf(void);

/* missing: 
 change proority
 - delete
 */

#endif
