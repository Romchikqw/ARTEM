#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

Table *Init(int count){
        Table *table = (Table *)calloc(1,sizeof(Table));
        table->msize = count;
        table->csize = 0;
        return (table);
}

int CheckSize(Table *table){
        if (table->csize == table->msize) return 1;
        return 0;
}

char *Find(Table *table,int key){
        Keyspace *temp;
        if (!table->ks1) return NULL;
        temp = table->ks1;
        while (temp){
                if (temp->key == key) return (temp->info);
                temp = temp -> next;
        }
        return NULL;
}

int Add(Table *table,int key,char *info){
        Keyspace *temp;
        Keyspace *ptr = (Keyspace *)calloc(1,sizeof(Keyspace));
        if (key == 0 || !info || table->csize >= table->msize) return 1;
        if (!table->ks1){
                ptr->key = key;
                ptr->info = info;
                table->ks1 = ptr;
                table->csize+=1;
                return 0;
        }
        temp = table->ks1;
        while (temp->next) temp = temp->next;
        ptr->key = key;
        ptr->info = info;
        temp->next = ptr;
        table->csize+=1;
        return 0;
}

int Delete(Table *table , int key){
        Keyspace *temp,*ptr;
        temp = table->ks1;
        if (temp->key == key){
                table->ks1 = temp->next;
		free(temp->info);
                free(temp);
                table->csize-=1;
                return 0;
        }
        while (temp){
                if (temp->next->key == key){
                        ptr = temp -> next;
                        temp -> next = ptr ->next;
			free(ptr->info);
                        free(ptr);
                        table->csize-=1;
                        return 0;
                }
                temp = temp->next;
        }
        return 1;
}

int Print(Table *table){
        Keyspace *temp;
        temp = table->ks1;
        printf("\nKey:    |Info:\n");
        while (temp){
                printf("%-9d|",temp->key);
                printf("%s\n",temp->info);
                temp = temp->next;
        }
        printf("\n");
        return 0;
}

int Clear(Table *table){
        Keyspace *temp,*ptr;
        temp = table->ks1;
        while (temp){
                ptr = temp;
                temp = temp->next;
                free(ptr->info);
                free(ptr);
        }
        free(table);
        return 0;
}

void Roma(Table *table,int a,int b){
        int i = a;
        int count = 0;
        char *info;
        while (i <= b){
                if (Find(table,i)) count+=1;
                i+=1;
        }
        printf("\n%d\n",count);
        Table *table1 = Init(count);
        while (a <= b){
                 if (Find(table,a)){
                        info = Find(table,a);
                        Add(table1,a,info);
                }
                a+=1;
        }
        Print(table1);
	Keyspace *temp,*ptr;
	temp = table ->ks1;
        while (temp){
                ptr = temp;
                temp = temp->next;
                free(ptr);
        }
        free(table1);
}

