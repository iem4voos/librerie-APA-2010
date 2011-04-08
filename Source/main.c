//libapa testing file

#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

 
#define fDBG(a) printf(#a "\n%f",a) 
#define cDBG(a) printf(#a "\n%c",a) 

int test_matrici(void);

int main(void){
    printf("...");
    
    test_matrici();
    
    return 0;
}

int test_matrici(void){
    
    float ***k=(float ***)initMatt3d( 3, 9, 3, float);
    char **m=(char**)initMatt2d(5, 2, char);
    
    k[0][1][2]=3;
    fDBG(k[0][1][2]);
    
    m[0][1]=3;
    cDBG(m[0][1]);
    
    freeMat2d( m ,5, 3); 
    freeMat3d( k ,3, 9, 3); 
    return 0;
}