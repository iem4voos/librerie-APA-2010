//
//  graph-algoritm-test.h
//  MicLibApa2010
//
//  Created by mic on 24/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef MicLibApa2010_graph_algoritm_test_h
#define MicLibApa2010_graph_algoritm_test_h

typedef struct bfs_resut_s  * bfs_result;
typedef struct dfs_resut_s  * dfs_result;


bfs_result  bfs_init(graph G);
void        bfsFreeResult(bfs_result R);
bfs_result  bfs_from(bfs_result handler, int fromEdge);
void        print_bfs_res(bfs_result R);

dfs_result dfs_visit_r(dfs_result handler,int fromEdge);

void bfs_selftest1(void);


#endif
