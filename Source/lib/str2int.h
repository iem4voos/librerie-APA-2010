//
//  str2int.h
//  MicLibApa2010
//
//  Created by mic on 14/08/11.
//

#ifndef MicLibApa2010_str2int_h
#define MicLibApa2010_str2int_h

#include <stdio.h>

typedef struct s2i_s *s2i;

s2i     str2intInit(int size);
void    str2intFree(s2i );

int     str2int(s2i,char *);
char *  int2str(s2i, int);

int     str2intLen(s2i);
void    str2intPrint(s2i );




#endif
