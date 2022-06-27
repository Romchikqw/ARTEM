#include <stdio.h>
#include <stdlib.h>
#include "operwtab.h"

int main(){
    int count;
    printf("Print count of of vertices:\n");
    scanf("%d",&count);
    int** matrix = INITM(&count);
    PRINTM(matrix,&count);
    DELETEEDGE(matrix,&count);
    PRINTM(matrix,&count);
    INSERTEDGE(matrix,&count);
    PRINTM(matrix,&count);
    matrix = INSERTVER(matrix,&count);
    PRINTM(matrix,&count);
    matrix = DELETEVER(matrix,&count);
    PRINTM(matrix,&count);
    S_FB(matrix,&count);
    BFS(matrix,&count);
    FREEM(matrix,&count);
    return 0;

}
