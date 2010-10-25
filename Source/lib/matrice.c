//  matrice.c  MicLibApa2010 Created by mic on 25/10/10.

#include "matrice.h"
#include <stdlib.h>

//MARK: 2D
void ** zInitMat2d(int R,int C, size_t dim){

    void ** mat;
    
    mat=(void **)malloc(sizeof(void *) * C);
    
    for(int j=0; j< R ; j++ ){
        mat[j]=(void*)calloc(C, dim);
    }
    return mat;
}

void zFreeMat2d(void **mat,int R,int C){
    
    for(int j=0; j< R ; j++ ){
        free(mat[j]);
    }
    free(mat);
}

//MARK: 3D
void *** zInitMat3d(int R,int C, int P, size_t dimensione){
    
    void ***mat;
    
    mat=(void ***)malloc(sizeof(void **) * R);
    for(int i=0; i< R ; i++){
        
        mat[i]=(void **)malloc(sizeof(void *) * C);
        
        for(int j=0; j< C ; j++ ){
            mat[i][j]=(void*)calloc(P, dimensione);
        }
    }
    return mat;
}


void zFreeMat3d(void ***mat,int R,int C, int P){
    
    
    for(int i=0; i< R ; i++){
        for(int j=0; j< C ; j++ ){
            free(mat[i][j]);
        }
        free(mat[i]);
    }
    free(mat);
    return;
}