#ifndef OPERWTAB_H
#define OPERWTAB_H

typedef struct queue{
        int* q;
        int head;
        int tail;
}queue;

int** INITM(int* count);
void PRINTM(int** matrix,int* count);
int DELETEE(int** matrix,int* count);
int** DELETEV(int** matrix,int *count);
int** INSERTV(int** matrix, int *count);
int INSERTE(int** matrix,int* count);
queue* INITQ(int count);
void BFS(int** matrix,int count);
void S_FB(int** matrix,int* count);
void FREEM(int** matrix,int *count);

#endif
