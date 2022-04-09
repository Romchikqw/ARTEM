#include <stdio.h>
#include <stdlib.h>
#include"Header.h"

void input(Matrix *m){
    int len, a;
    int i, j;
    printf("Введите количество строк:\n");
    scanf("%d", &len);
    m->line = len;
    m->l= (lines*) malloc(len * sizeof(lines));
    for (i = 0; i < m->line; i++){
        printf("Введите количество элементов в строке\n");
        scanf("%d",&a);
        if (a > 0){
            m->l[i].elem = a;
            m->l[i].mas = malloc(a*sizeof(int));
            printf("Введите элементв строки:\n");
            for (j = 0; j < m->l[i].elem; j++){
                scanf("%d",&m->l[i].mas[j]);
            }
        }
    }
}


