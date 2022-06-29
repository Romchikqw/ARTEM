#include "operations.h"
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int Menu(const char *msg[],int count,item *root){
    int i;
    int key;
    char *info1;
    item *max;
    for (i = 0;i<count;i++){
        printf("%s\n",msg[i]);
    }
    printf("\nEnter a number:\n");
    scanf("%d",&i);

    switch(i){
        case 1:
            printf("Bye!\n");
            return 0;
            break;
        case 2:
            info1 = calloc(10, sizeof(char));
            printf("Enter your key\n");
            scanf("%d",&key);
            printf("Enter info\n");
            scanf("%s",info1);
            insert(root,key,info1);
            return 1;
            break;
        case 3:
            printf("Enter delete  key\n");
            scanf("%d",&key);
            delete(root,key);
            return 2;
            break;
        case 4:
            printf("Enter search key\n");
            scanf("%d",&key);
            item *find = search(root,key);
            printf("\n%s\n", find->info);
            return 3;
            break;
        case 5:
            printf("Enter search max key\n");
            scanf("%d",&key);
            item *findm = search_max(root,key);
            printf("\n%d\n", findm->key);
            return 4;
            break;
        case 6:
            print(root);
            printf("\n");
            return 5;
            break;
    }

}

int main() {

    int key,i = 6;
    int flag;
    char *msg[] = {"1.Quit","2.Insert new element","3.Delete element","4.Search element","5.Search max element","6.Print tree"};
    char *info = calloc(20,sizeof(char)) ;

    printf("Enter the root element key :\n");
    scanf("%d",&key);
    printf("Enter the root element info :\n");
    scanf("%s",info);
    item *root = init(key,info);

    do {
        flag = Menu(msg,i,root);
    }while (flag > 0 && flag <6);

    clear(root);
    return 0;
}
