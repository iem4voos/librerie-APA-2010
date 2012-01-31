//
//  topological-sort.h
//  MicLibApa2010
//
//  Created by mic on 31/01/12. All rights reserved.


#ifndef MicLibApa2010_topological_sort_h
#define MicLibApa2010_topological_sort_h

#include "graph.h"
#include "coda.h"
// REQUIRE #include "graph-dfs.h"
coda topological_sort(graph G);

coda topological_sort_SelfTest(graph G);
#endif
