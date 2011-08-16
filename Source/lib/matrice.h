//  matrice.h MicLibApa2010 Created by mic on 25/10/10. 
#ifndef _matrice_H_
#define _matrice_H_

#include <stdlib.h>

//---------------------------------------------------------
// Questa libreria permette di creare e liberare la memoria 
// per matrici quadrate e cubiche
//
// uso: 
//        float **mat_2d=(float **)initMatt2d( 25, 3, float);
//        float ***mat_3d=(float ***)initMatt3d(7, 9, 5, float);
//
//        mat_2d[x][y]=z;
//        mat_3d[j][k]=l;
//        
//        freeMat2d( mat_2d ,25,3);
//        freeMat3d( mat_3d ,7, 9, 5);
//---------------------------------------------------------

//TODO: rivedere le macro: sizeof(#tipo) potrebbe restituire la lunghezza della stringa e non il valore corretto

//2D
#define initMatt2d(x,y,tipo) zInitMat2d(x,y,sizeof(#tipo))
#define freeMat2d(mat,x,y) zFreeMat2d((void **)mat,x,y)
//3D
#define initMatt3d(x,y,z,tipo) zInitMat3d(x,y,z,sizeof(#tipo))
#define freeMat3d(mat,x,y,z) zFreeMat3d((void ***)mat,x,y,z)


//2D
void ** zInitMat2d(int R,int C, size_t dim);
void zFreeMat2d(void **mat,int R,int C);
//3D
void *** zInitMat3d(int R,int C, int P, size_t dim);
void zFreeMat3d(void ***mat,int R,int C, int P);

void * initMattNd(int ,...);

#endif // #ifndef _matrice.h_H_
