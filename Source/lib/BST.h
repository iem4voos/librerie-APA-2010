//
//  BST.h
//  Esame-22-2-12
//
//  Created by mic on 23/02/12.
//  Copyright (c) 2012 Michail Ivanov. All rights reserved.
//

#ifndef MicLibApa_BST_h
#define MicLibApa_BST_h

typedef enum{PRE_ORDER,POST_ORDER,IN_ORDER} bst_visit_order;

typedef struct BST_s *BST;

BST BSTinit(int(* compare)(void *, void *));
int BST_insert(BST, void *);

int BST_delByCompare(BST,void *, int(* compare)(void *, void *));

void BST_visitWithFunctionAndPtr(BST B, int (*func)(void *, void *), void *, bst_visit_order);
void * BST_Delete(BST t, void * itemIn);

void   BST_selftest(void);
void * BST_serch(BST t, void *a);

#endif
