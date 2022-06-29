#include <stdio.h>
#include <stdlib.h>
#include "operwtab.h"

int main(){
    int count;
    printf("Print count of of vertices:\n");
    scanf("%d",&count);
    int** matrix = INITM(&count);
    PRINTM(matrix,&count);
    DELETEE(matrix,&count);
    PRINTM(matrix,&count);
    INSERTE(matrix,&count);
    PRINTM(matrix,&count);
    //matrix = INSERTV(matrix,&count);
    PRINTM(matrix,&count);
    matrix = DELETEV(matrix,&count);
    PRINTM(matrix,&count);
    S_FB(matrix,&count);
    //BFS(matrix,count);
    PRINTM(matrix,&count);
    FREEM(matrix,&count);
    return 0;

}
