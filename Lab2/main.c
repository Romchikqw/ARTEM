#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct info_pas{
    char *name;
    int ta;
    int ts;
}info_pas;


typedef struct item_list{
    struct info_pas passanger;
    struct item_list *next;
}item_list;

typedef struct list{
    struct item_list *first;
    struct item_list *last;
    int count;
}list;

list *init(int count){
    list *list1 = calloc(1,sizeof(list));
    list1->count = count;
    return list1;
}

item_list *readitem(char *str){
    char tok[2] = "/";
    item_list *temp = calloc(1,sizeof(item_list));
    temp->passanger.name = strtok(str,tok);
    temp->passanger.ta = atoi(strtok(NULL,tok));
    temp->passanger.ts = atoi(strtok(NULL,tok));
    return temp;
}

int push(list *list, item_list *temp){
    if (list->first == NULL){
        list->first = temp;
        list->last = temp;
        list->count++;
        temp->next = NULL;
        return 0;
    }
    else {
        item_list *ptr = list->last ;
        ptr->next= temp;
        list->last = temp;
        list -> count ++;
        return 0;
    }
}

char *my_itoa(int num, char *str){
	if(str == NULL)	{
		return NULL;
	}
	sprintf(str, "%d", num);
	return str;
} 

int pop(list *list){
    if (!list->first) return 1;
    item_list *temp = list->first;
    if (temp->next) list->first = temp->next;
    else list->first = NULL;
    free(temp->passanger.name);
    free(temp);
    return 0;
}

item_list *peek(list *list){
    if (!list->first) return NULL;
    item_list *temp = list->first;
    return temp;
}

int get_count_p(list *list){
    int count = 0;
    item_list *temp = list->first;
    item_list *next;
    printf("          |");
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

int main(){
    int i = 1,count_st,count_pas;
    char *info;
    int count;

    printf("Enter count of stage:\n");
    scanf("%d",&count_st);
    printf("Enter count of passengers:\n");
    scanf("%d",&count_pas);
    int i1 = count_pas;
    char ***table;
    list *list = init(count_pas);

    table = (char ***)malloc(count_st*sizeof(char **));
    while (i1 > 0){
        printf("Enter info about %d passenger:",i);
        i++;
        info = (char *)calloc(10,sizeof(char)) ;
        scanf("%s",info);
        item_list *temp;
        temp = readitem(info);
        push(list,temp);
        i1--;
    }
    count = get_count_p(list);
    for (int i2 = 0;i2<count_st;i2++){
        table[i2] = (char **)malloc(count*sizeof(char *));
    }
    for (int i3 = 0 ;i3<count_st;i3++){
        char num[7] = "Stand ";
	char i1[2];
        my_itoa(i3+1,i1);
        strcat(num,i1);
        strcat(num,"|");
        table[i3][0] = (char *)calloc(10,sizeof(char));
        strcpy(table[i3][0],num);
    }
    char *no;
    no = "       ";
    int j = 1;
    while (j<=count){
        i = 0;
        table[i][j] = (char *)calloc(10,sizeof(char));
        item_list *temp = peek(list);
        strcpy(table[i][j],temp->passanger.name);
        pop(list);
        while (peek(list) && temp->passanger.ta == peek(list)->passanger.ta){
            i++;
            table[i][j] = (char *)calloc(10,sizeof(char));
            strcpy(table[i][j] ,peek(list)->passanger.name);
            pop(list);
        }
        i++;
        while (i < count_st){
            table[i][j] = (char *)calloc(10,sizeof(char));
            strcpy(table[i][j],no);
            i++;
        }
        j++;
    }
    for (int j = 0;j<count_st;j++){
        for (int i = 0;i<=count;i++){
            printf("%8s",table[j][i]);
        }
        printf("\n");
    }
    for (int i = 0;i<count_st;i++){
        for (int j = 0;j<=count;j++){
            free(table[i][j]);
        }
        free(table[i]);
    }
    free(table);
    free(list);
    printf("That's all! Bye!\n");
    return 0;


}

