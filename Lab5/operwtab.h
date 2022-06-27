#ifndef OPERWTAB_H
#define OPERWTAB_H

typedef struct queue{
        int* q;
        int head;
        int tail;
}queue;

int** INITM(int* count);
void PRINTM(int** matrix,int* count);
int DELETEEDGE(int** matrix,int* count);
int** DELETEVER(int** matrix,int *count);
int** INSERTVER(int** matrix, int *count);
int INSERTEDGE(int** matrix,int* count);
queue* INITQ(int count);
void push(queue* queue,int v);
int* pop(queue *queue);
void balanceQ(queue *q);
void BFS(int** matrix,int*count);
void S_FB(int** matrix,int* count);
void FREEM(int** matrix,int *count);

#endif
