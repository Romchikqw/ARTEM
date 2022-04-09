#include <stdio.h>
#include <stdlib.h>
#include"Header.h"



void output(Matrix *m){
    int i,i1;
    for (i = 0;i< m->line;i++){
        for (i1 = 0;i1 < m->l[i].elem;i1++){
            printf("%d ",m->l[i].mas[i1]);
        }
        printf("\n");
    }
}



