#include <stdio.h>
#include <stdlib.h>

int** INITM(int *count){
    int **matrix = (int **)calloc(*count,sizeof(int*));
    for (int i = 0;i<*count;i++) matrix[i] = (int *)calloc(*count,sizeof(int));
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

int** INSERTV(int** matrix,int *count){
    int i ;
    for (int j = 0;j<*count;j++){
        int weight;
        printf("Enter the weight of the edge beetween the vercites (%d) (%d)\n",(j+1),*count+1);
        scanf("%d",&weight);
        matrix[j][*count] = matrix[*count][j] = weight;
    }
    matrix[*count][*count] = 0;
    (*count)++;
    return matrix;
}

int** DELETEV(int** matrix,int *count){
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

int INSERTE(int** matrix,int *count){
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

int DELETEE(int** matrix,int *count){
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

void BFS(int** matrix,int*count){
	int v1,v2;
	printf("Enter first vertex:\n");
	scanf("%d",&v1);
	printf("Enter second vertex:\n");
        scanf("%d",&v2);
	for (int i = 0; i<(*count);i++){
		for (int j = 0; j<(*count);j++){
			if (matrix[v1][v2] == *count) printf("%d\n",matrix[v1][v2]);
		}
	}
	return;
	
}

void S_FB(int** matrix,int* count){
	int* distances = (int *)calloc(*count,sizeof(int));
	int i = 0;
	while (i<(*count)){
		int i1 = 0;
		while (i1<(*count)){
			int j1 = 0;
			while (j1 < (*count)){
				if (distances[j1] > (distances[i1] + matrix[i1][j1])){
					 distances[j1] = (distances[i1]+matrix[i1][j1]);
				}
			}
		}

	}
	for (int i = 0 ; i<(*count) ; i++){
		printf("(V%d) : %d	\n",i+1,distances[i]);
	}
	free(distances);
}

/*int get_count_p(int** matrix){
    int count = 0;
    item_list *temp = list->first;
    item_list *next;
    printf("       |");
    printf("%8d|",temp->passanger.ta);
    next = temp;
    temp = temp->next;
    while (next->next){
        if (next->passanger.ta != temp->passanger.ta) {
            printf("%8d|", temp->passanger.ta);
            count++;
        }
        next = next->next;
        temp = temp->next;
    }
    printf("\n");
    return (count+1);
}
*/

void FREEM(int** matrix,int *count){
    for (int i = 0;i<(*count);i++) free(matrix[i]);
    free(matrix);
}
