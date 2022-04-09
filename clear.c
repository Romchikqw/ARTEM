#include <stdio.h>
#include <stdlib.h>
#include"Header.h"




void clear(Matrix *m){
    int i = 0;
    while (i< m->line){
        free(m->l[i].mas);
        i++;
    }
    free(m->l);
    m->line = 0;
    m->l = NULL;
}





