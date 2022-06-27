#include <stdio.h>
#include <stdlib.h>

int** INITM(int *count){
    int **matrix = (int **)calloc(*count,sizeof(int*));
    for (int i = 0;i<*count;i++){
        matrix[i] = (int *)calloc(*count,sizeof(int));
    }
    for (int i = 0;i<*count;i++){
        for (int j = i;j<*count;j++){
            if (i != j && !matrix[j][i]) {
                printf("Enter the weight of the edge between the vertices (%d) (%d):", i, j);
                scanf("%d", &(matrix[i][j]));
                matrix[j][i]= matrix[i][j];
            }
        }
    }
    return matrix;
}

void PRINTM(int** matrix,int *count) {
    printf("   ");
    for (int i = 0; i < *count;i++) printf ("%d  ",i+1);
    printf("\n");
    for (int i = 0; i < *count; i++) {
	printf ("%d  ",i+1);
        for (int j = 0; j < *count; j++) printf("%d  ", matrix[i][j]);
        printf("\n");
    }
}

int** INSERTVER(int** matrix,int *count){
    int i ;
    matrix = (int **)realloc(matrix,(*count+1)*sizeof(int *));
    for (i = 0;i<*count;i++) matrix[i] = (int *)realloc(matrix[i],(*count+1)*sizeof(int));
    matrix[*count]=(int *)calloc((*count+1),sizeof(int));
    for (int j = 0;j<*count;j++){
        int weight;
        printf("Enter the weight of the edge beetween the vercites (%d) (%d)\n",(j+1),*count+1);
        scanf("%d",&weight);
        matrix[j][*count] = matrix[*count][j] = weight;
    }
    matrix[*count][*count] = 0;
    ++(*count);
    return matrix;
}

int** DELETEVER(int** matrix,int *count){
	printf("Enter delete vertex:\n");
	int vertex;
	scanf("%d",&vertex);
	for (int i = 0;i < (*count);i++){
		for (int j = vertex-1;j<(*count-1);j++){
			matrix[i][j]=matrix[j][i]=matrix[i][j+1];
			if (i == j) matrix[i][j] = 0;
		}
	}
	free(matrix[*count-1]);
	matrix = (int **)realloc(matrix,(*count-1)*sizeof(int *));
        for (int i = 0;i<(*count-1);i++) matrix[i] = (int *)realloc(matrix[i],(*count-1)*sizeof(int));
	(*count)--;
	return matrix;
}

int INSERTEDGE(int** matrix,int *count){
	printf("which vertices do you want to insert the edge:\nEnter first vertex:\n");
        int first;
        scanf("%d",&first);
        printf("Enter second vertex:\n");
        int second;
        scanf("%d",&second);
        if (matrix[first-1][second-1]){
                printf("The edge already exists\n");
                return 1;
        }
	printf("Enter weight of edge\n");
	int weight;
	scanf("%d",&weight);
        matrix[first-1][second-1] = matrix[second-1][first-1] = weight;
        return 0;
} 

int DELETEEDGE(int** matrix,int *count){
	printf("which vertices do you want to remove the edge:\nEnter first vertex:\n");
	int first;
	scanf("%d",&first);
	printf("Enter second vertex:\n");
	int second;
	scanf("%d",&second);
	if (!matrix[first-1][second-1]){
		printf("The edge no longer exists\n");
		return 1;
	}
	matrix[first-1][second-1] = matrix[second-1][first-1] = 0;
	return 0;
}

typedef struct queue{
        int* q;
        int head;
        int tail;
}queue;

queue* INITQ(int count){
	queue* queue = calloc(1,sizeof(queue));
	queue->q = (int *)calloc(count,sizeof(int));
	queue->head = 0;
	queue->tail = 0;
	return queue;
}

void push(queue* queue,int v){
	queue->q[queue->head] = v;
	++(queue->tail);
}

int pop(queue *queue){
	int v = queue->q[queue->head];
	++(queue->head);
	return v;
}

void balanceQ(queue* q) {
    --(q->tail);
    --(q->head);
    for (int i = q->head; i < q->tail; ++i) {
        q->q[i] = q->q[i+1];
    }
}

void BFS(int** matrix,int*count){
	int v1,v2;
	printf("Enter first vertex:\n");
	scanf("%d",&v1);
	printf("Enter second vertex:\n");
        scanf("%d",&v2);
	int* color = (int *)calloc(*count,sizeof(int));
	queue* queue = INITQ(*count);
	for (int i = 0 ; i < (*count) ;i++) color[i] = 0;
	color[v1] = 1;
	push(queue,v1);
	printf("Path from vertex %d to vertex %d:  ",v1,v2);
	while (queue->head != queue->tail){
		int v = pop(queue);
		balanceQ(queue);
		for (int i = 0;i < (*count);i++){
			if (matrix[v1][i] == v2){
                                printf("Yeah!\n");
                                return;
                        }
			if (!color[i]){
				push(queue,v);
				printf("%d ",v);
				color[i] = 1;
			}
		}
	printf("\n");
	free(queue->q);
	free(queue);
	free(color);
	return;
	}
}

void S_FB(int** matrix,int* count){
	int* distances = (int *)calloc(*count,sizeof(int));
	printf("Enter vertex:\n");
	int d_ver;
	scanf("%d",&d_ver);
	d_ver--;
	for (int i = 0;i<(*count);i++) distances[i] = 1000;
	distances[d_ver] = 0;
	for (int i = 0;i<(*count);i++){
		for (int i1 = 0;i1<(*count);++i1){
			for (int j1 = 0;j1 <(*count);++j1){
				if (matrix[i1][j1]){
					if (distances[j1] > (distances[i1] + matrix[i1][j1])){
						 distances[j1] = (distances[i1]+matrix[i1][j1]);
					}
				}
			}
		}

	}
	for (int i = 0 ; i<(*count) ; i++){
		printf("(V%d) : %d	\n",i+1,distances[i]);
	}
	free(distances);
}

void FREEM(int** matrix,int *count){
    for (int i = 0;i<(*count);i++) free(matrix[i]);
    free(matrix);
}
