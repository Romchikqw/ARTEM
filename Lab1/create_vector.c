#include <stdio.h>
#include <stdlib.h>
#include"Header.h"




int check(int* mas, int length){
    int i;
    for (i = 0; i < length; ++i) {
        if (mas[i] <= 0) {
            return mas[length-1];
        }
    }
    return mas[0];
}

int* my_func(Matrix* m){
    int i = 0;
    int* mas1 = (int*) malloc(m->line*sizeof(int));
    printf("Our new vector:");
    while (i < m->line){
        mas1[i] = check(m->l[i].mas, m->l[i].elem);
        printf(" %d", mas1[i]);
        i++;
    }
    printf("\n");
    return mas1;
}
