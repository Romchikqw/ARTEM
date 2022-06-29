#include <stdio.h>
#include <stdlib.h>
#include"Header.h"


int main(){
    Matrix m = {0, NULL};
    input(&m);

    if (m.line != 0) {
        printf("Введённая матрица:\n");
        output(&m);
    } else {
        printf("Неверный ввод!\n");
        return 0;
    }

    int* vector = NULL;
    vector = my_func(&m);

    clear(&m);
    free(vector);

    return 0 ;
}
