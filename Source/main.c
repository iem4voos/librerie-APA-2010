//  main.c librerie-APA-2010  Created by mic on 08/09/10.

#include <stdio.h>
#include "lib/coda.h"

int main (int argc, const char * argv[]) {
    char str[]="parolalunga";
    coda C=codaInit();

    puts("------ test lib -------");
    
        //aggiungo elementi alla coda
    for(int i=0; str[i]!='\0'; codaAppend(C, &str[i++]) );

        //stampo gli elemeti in coda
    for(char *c; (c=(char *)codaGet(C)) ; printf(">>%c<<\n",*c) );
    
    return 0;
}

