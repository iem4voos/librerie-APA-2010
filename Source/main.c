//libapa testing file

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "lib/matrice.h"
#include "lib/str2int.h"
#include "lib/coda.h"
#include "lib/union-find.h"
#include "lib/graph.h"
#include "lib/heap.h"
#include "lib/graph-algoritm-test.h"

#include "topological-sort.h"

#define macro(stringa) sizeof(#stringa)
 
#define fDBG(a) printf(#a "\n%f",a) 
#define cDBG(a) printf(#a "\n%c",a) 

int test_matrici(void);
void test_int2str(void);
void  test_coda(void);

void zz(int v[4],int c){
    for (int i =0; i<c; i++) {
        printf("> %d \n",v[i]);
    }
}



int main(void){
    printf("...\n");
    
    //bfs_selftest1();
    
    //heapSelf();
    //graph G= graph_selftest1();
    //graphFree(G);
    
    topological_sort_SelfTest(NULL);
    
    //test_coda();
    //coda_selfTest1();
    //uf_selftest();
    //assert( macro(char) == sizeof(char) );
    //test_matrici();
    //test_int2str();
    puts("fine");
    
    return 0;
}

void  test_coda(void){

    coda C;
    int nums[6]={1,5,33,3,24,2};
    
    C = codaInitNumeric();
    for (int i=0; i<6; i++) {
        codaPush(C, &nums[i]);
    }
    
    for (int i=0; !codaIsEmpty(C); i++) {
        //printf("+%d ", *(int*)codaGet(C) );
       printf("-%d ", *(int*)codaPop(C) );
    }
}

void test_int2str(void){
    puts(".............\n stat testing str2int Lib \n..............");
    
    s2i S;
    S = str2intInit(2);
    
    puts("aggiungo per 3 volte la stessa stringa");
    for (int i=0; i< 3; i++) {
        printf("%d - %s - len: %d\n", str2int(S, "coso"),"coso" ,str2intLen(S));
        //str2intPrint(S );
    }
    
    puts("aggiungo manualmente 2 diverse");
    printf("%d - %s\n", str2int(S, "rosa"),"rosa" ); //str2intPrint(S );
    printf("%d - %s\n", str2int(S, "rapa"),"rapa" ); // str2intPrint(S );
    
    puts("aggiungo per 3 volte la stessa stringa");
    for (int i=0; i< 3; i++) {
        printf("return int :%d - %s - len of vector: %d\n", str2int(S, "marmotta"),"marmotta" ,str2intLen(S));
        //str2intPrint(S );
    }
    
    puts("stampa di tutti gli elementi contenuti nella struttura");
    for (int i=0; i< str2intLen(S); i++) {
        printf("> %s \n", int2str(S, i));
    }
    
    str2intFree(S);
    puts("end of test \n...................");

    
}

int test_matrici(void){
    
    float ***k=(float ***)initMatt3d( 3, 9, 3, float);
    char **m=(char**)initMatt2d(5, 2, char);
    
    /*
     float ***k=(float ***)zInitMat3d( 3, 9, 3, sizeof(float));
     char **m=(char**)zInitMat2d(5, 2, sizeof(char));
     */
    
    k[0][1][2]=3;
    fDBG(k[0][1][2]);
    
    m[0][1]=3;
    cDBG(m[0][1]);
    
    freeMat2d( m ,5, 3); 
    freeMat3d( k ,3, 9, 3); 
    return 0;
}