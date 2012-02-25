//
//  BST.c
//  Esame-22-2-12
//
//  Created by mic on 23/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "BST.h"


typedef struct node_s *node;

struct BST_s{
    node root; 
    int(* compare)(void *, void *);
    int count;
};

struct node_s {
    void *item;
    node left;
    node right;
    node father;
};

void insert_r(BST B,node n, void *item );
void visitWF( node n, int (*func)(void *, void *), void * item,bst_visit_order);
node newNode(void * item, node);

node newNode(void * item, node father){
    node n=malloc(sizeof(struct node_s));
    n->left=n->right=NULL;
    n->item=item;
    n->father=father;
    return n;
}

BST BSTinit(int(* compare)(void *, void *)){
    BST theBst;
    
    theBst = malloc(sizeof(struct BST_s));
    theBst->root=NULL;
    theBst->compare=compare;
    
    theBst->count=0;
    
    return theBst;
}

int BST_insert(BST B, void * item){
    if (B->root== NULL) {
        B->root = newNode(item,NULL);
        return 1;
    }
    
    insert_r(B, B->root, item);
    
    return 1;
}


void insert_r(BST B,node n, void *item ){
    
    if (B->compare( item,n->item) > 0) { // maggiore
        if (n->right == NULL) {
            n->right=newNode(item,n);
            return;
        }else{
            insert_r(B, n->right, item);
        }
    }else{
        if (n->left == NULL) {
            n->left = newNode(item,n);
            return;
        }else{
            insert_r(B, n->left, item);
        }
    }
}

void BST_visitWithFunctionAndPtr(BST B, int (*func)(void *, void *), void * item, bst_visit_order order){
    if (B->root== NULL) return;
    visitWF( B->root, func, item, order);
}

void visitWF(node n, int (*func)(void *, void *), void * item, bst_visit_order order){
    
    switch (order) {
        case PRE_ORDER:
            func(n->item, item);
            if (n->left)  visitWF( n->left , func, item,order);
            if (n->right) visitWF( n->right, func, item,order);
            break;
        case IN_ORDER:
            if (n->left)  visitWF( n->left , func, item,order);
            func(n->item, item);
            if (n->right) visitWF( n->right, func, item,order);
            break;
        case POST_ORDER:
            if (n->left)  visitWF( n->left , func, item,order);
            if (n->right) visitWF( n->right, func, item,order);
            func(n->item, item);
            break;
    }
}

int BST_delByCompare(BST B,void * item, int(* compare)(void *, void *)){
    
    
    return 1;
}

//MARK: - jjj
//void * BST_Delete(BST t, void * itemIn);

static node bstSerchR(BST t,node n, void *a);


static node min(node n);
static void extract2(BST t, node this);

void * BST_serch(BST t, void *a){
    
    
    if (t->root==NULL) {
        //puts("albero vuoto..ricerca impossibile..");
        return NULL;
    }
    
    node n=bstSerchR(t,t->root, a);
    
    if(n!=NULL)
        return n->item;
    else{
        //puts("no result!!");
        return NULL;
    }
}
static node bstSerchR(BST t,node n, void *a){
    
    if (n==NULL) {
        //puts("strano nodo passato nullo");
        return NULL;
    }
    int result=t->compare(n->item, a);
    
    switch (result) {
        case 0:
            return n;
        case -1:
            return bstSerchR(t,n->right, a);
        case 1:
            return bstSerchR(t,n->left, a);
    } 
    return NULL;
}



void * BST_Delete(BST t, void * itemIn){
    node z= bstSerchR(t, t->root, itemIn);
    
    //if node has NO childen delete it
    
    if ( z->left==NULL || z->right==NULL ) // only one child
    {
        //if node has ONLY ONE children extract it
        //puts("cancello nodo con un solo figlio..");
        //printf("> %d\n" , *(int *)z->item);
        
        extract2(t, z);
    }
    else          //if it has bath childrens esctract sucessor, exchange sucessor with item
    {
        node suc=min(z->right); // find successor
        
        //puts("cancello nodo con due figli..");
        //printf("> %d\n" , *(int *)z->item);
        //printf(">sucessor %d\n" , *(int *)suc->item);
        
        extract2(t, suc);
        
        //!-- substitute the extracted ode with sucessor--
        // link correctly the substituto
        suc->left=z->left;
        suc->right=z->right;
        suc->father=z->father; //z facher can be null but it'ok couse z is root
        
        //liink th root if necessary
        if (z==t->root)
            t->root=suc;
        else
            if (z==z->father->left) 
                z->father->left=suc;
            else
                z->father->right=suc;
        
        //unlink relink father and soons
        if (z->left != NULL)  z->left->father = suc;
        if (z->right!= NULL)  z->right->father= suc;
        
        //delete the extracted node
    }
    void * item=z->item;
    free(z); 
    return item;
}

// works if only one or none childs


static void extract2(BST t, node this){
    
    node father=this->father, son; //father can be null- if thi is root
    
    if (this->left!=NULL) {
        son= this->left;
    }else
        son=this->right;
    // son can be null
    
    if (son!=NULL) son->father=father; // father can be null
    
    if (this == t->root) { //if root link son to root
        t->root=son;
    }else
        if (father->left == this)
            father->left=son; //attach to left of father
        else
            father->right=son; //attach to right of father
    
    t->count--;
    
}

static node min(node n){
    if( n == NULL ) return NULL;
    if( n->left == NULL ) return n;
    
    return min( n->left );
}

//MARK: - selftest

int confronta(void *a, void *b);
int stampa(void *a, void *b);

int confronta(void *a, void *b){
    
    int *x=a, *y=b;
    
    if (*x > *y)
        return 1;
    else if(*x == *y)
        return 0;
    else
      return -1;
}

int stampa(void *a, void *b){
    int *x=a;
    
    printf("%d", *x);
    
    return 1;
}

void BST_selftest(void){
    
    BST B=BSTinit(confronta);
    
    int array[]={2,5,3,4 , 7,5,3,1};
    
    for (int i=0; i<8; i++) {
        BST_insert(B, &array[i]);
    }
    

    BST_visitWithFunctionAndPtr(B, stampa, NULL,IN_ORDER);
    puts("\n");
    BST_visitWithFunctionAndPtr(B, stampa, NULL,PRE_ORDER);
    puts("\n");
    BST_visitWithFunctionAndPtr(B, stampa, NULL,POST_ORDER);
    puts("\n");

    
    BST_Delete(B, &array[4]);
    BST_visitWithFunctionAndPtr(B, stampa, NULL,PRE_ORDER);
    puts("\n");
}









