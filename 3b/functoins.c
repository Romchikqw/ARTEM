#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

Table *Init(int count){
        Table *table = (Table *)calloc(1,sizeof(Table));
        table->count = count;
	table->n = 0;
        return table;
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
    if (key == 0 || !info) return 1;
    if (!table->ks1){
        ptr->key = key;
        ptr->info = info;
        table->ks1 = ptr;
        table->count+=1;
        return 0;
    }
    temp = table->ks1;
    while (temp->next) temp = temp->next;
    ptr->key = key;
    ptr->info = info;
    temp->next = ptr;
    table->count+=1;
    return 0;
}

int AddforTable(Table *table,int key,char *info){
    Keyspace *temp;
    Keyspace *ptr = (Keyspace *)calloc(1,sizeof(Keyspace));
    if (key == 0 || !info) return 1;
    if (!table->ks1){
        ptr->key = key;
        ptr->info = info;
        table->ks1 = ptr;
        table->n+=1;
        return 0;
    }
    temp = table->ks1;
    while (temp->next) temp = temp->next;
    ptr->key = key;
    ptr->info = info;
    temp->next = ptr;
    table->n+=1;
    return 0;
}

int AddforFile(Table *table,int key,char *info,FILE *f1,FILE *f2){
        Keyspace *temp;
        Keyspace *ptr = (Keyspace *)calloc(1,sizeof(Keyspace));
        if (key == 0 || !info) return 1;
        if (!table->ks1){
                int offset = ftell(f2);
                int takeoff = strlen(info);
                fwrite(&offset,sizeof(int),1,f1);
                fwrite(&takeoff,sizeof(int),1,f1);
                fwrite(&key,sizeof(int),1,f2);
                fwrite(info,sizeof(char),strlen(info) + 1,f2);
		ptr->key = key;
                ptr->info = info;
                table->ks1 = ptr;
                table->n+=1;
                return 0;
        }
        temp = table->ks1;
        while (temp->next)
		temp = temp->next;
        int offset = ftell(f2);
        int takeoff = strlen(info);
        fwrite(&offset,sizeof(int),1,f1);
        fwrite(&takeoff,sizeof(int),1,f1);
        fwrite(&key,sizeof(int),1,f2);
        fwrite(info,sizeof(char),strlen(info) + 1,f2);
        ptr->key = key;
        ptr->info = info;
        temp->next = ptr;
        table->n+=1;
        return 0;
}

void Createelfromfile(Table *table,int takeoff,FILE *f2){
        int key;
        char *info = (char *) calloc(takeoff + 1, sizeof(char));
        fread(&key,sizeof(int),1,f2);
        fread(info,sizeof(char),takeoff + 1,f2);
        AddforTable(table,key,info);
}

int Readfromfile(Table *table,FILE *f1,FILE *f2,int count){
        int offset = 0;
        int takeoff = 0;
        for (int i = 0; i < count - 1; i++) {
		if (feof(f1)) return 0;
                fread(&offset,sizeof(int),1,f1);
                fread(&takeoff,sizeof(int),1,f1);
                Createelfromfile(table,takeoff,f2);
        }
        return 0;
}

int Delete(Table *table , int key,FILE *f1,FILE *f2){
        Keyspace *temp,*ptr;
        temp = table->ks1;
        if (temp->key == key){
                table->ks1 = temp->next;
                free(temp);
                table->count-=1;
        }
        while (temp) {
                if (temp->next->key == key){
                        ptr = temp -> next;
                        temp -> next = ptr ->next;
                        free(ptr);
                        table->count-=1;
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
	int i = 0;
        while(temp){
		//if (i == (table->count - 1 )) break;
		if (temp->key>10000) return 0;
                printf("%-9d|",temp->key);
                printf("%s\n",temp->info);
                temp = temp->next;
		i++;
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
        temp = table1->ks1;
        while (temp){
                ptr = temp;
                temp = temp->next;
                free(ptr);
        }
        free(table1);
}
