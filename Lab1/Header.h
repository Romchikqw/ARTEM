#include <stdio.h>

typedef struct lines{
    int elem;
    int *mas;
}lines;

typedef struct Matrix{
    int line;
    lines *l;
}Matrix;

void input(Matrix *m);
void output(Matrix *m);
void clear(Matrix *m);
int check(int* mas, int length);
int* my_func(Matrix* m);
int main();










