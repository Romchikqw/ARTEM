#include "functoins.h"
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int Menu(const char *menu[],int a,Table *table,FILE *f1,FILE *f2){
        int i ;
        int choose;
        int key;
        int c,b;
        printf("\n");
        for (i = 0 ; i < a ; i++ ) printf("%s\n",menu[i]);
        printf("\n");
        scanf("%d",&choose);
        switch(choose){
                case 1:
                        return 0;
                        break;
                case 2:
                        printf("Insert your key\n");
                        scanf("%d",&key);
                        if (Find(table,key )){
                                printf("The key already exist\n");
                        }
                        else{
                                printf("Insert your info\n");
                                char *info = (char *)calloc(25,sizeof(char));
                                scanf("%s",info);
                                AddforFile(table,key,info,f1,f2);
                        }
                        return 1;
                        break;
                case 3:
                        printf("\nEnter the required key\n");
                        scanf("%d",&key);
                        if (!Find(table,key)){
                                printf("Element key not found\n");
                        }
                        else printf("%s\n\n",Find(table,key));
                        return 2;
                        break;
                case 4:
                        printf("Enter the key to be deleted\n");
                        scanf("%d",&key);
                        if (!Find(table,key)){
                                printf("Element key not found\n");
                        }
                        else Delete(table,key,f1,f2);
                        return 3;
                        break;
                case 5:
                        if (table) Print(table);
                        else printf("Table is emply\n");
                        return 4;
                        break;
                case 6:
                        printf("Enter a range of keys\n");
                        scanf("%d",&c);
                        scanf("%d",&b);
                        Roma(table,c,b);
                        return 5;
                        break;
        }
        return 0;
}

int main(){
        const char *menu[]={"1.Quit","2.Insert element","3.Find element be key","4.Delite element","5.Print table","6.Create by segment"};
        char *enter = "Enter your choice =>\n";
        int count;
        int flag;
	char *fname;
	char *fname2;
	Table *table;

	printf("Enter name of first file:\n");
	fname = readline("");
	FILE* f1 = fopen(fname,"r+b");
	FILE *f2;
	if (!f1){
        	printf("Enter the size of table:\n");
        	scanf("%d",&count);
        	while (count == 0){
        	printf("Введите другое значение!\n");
        	scanf("%d",&count);
        	}
		    f1 = fopen(fname,"w+b");
		    table = Init(count);
	            table->n = 0;
		    printf("Enter name of second file:\n");
	        fname2 = readline("");
		    f2 = fopen(fname2,"w+b");
	}
	else{
		printf("Enter name of second file:\n");
		fname2 = readline("");
		f2 = fopen(fname2,"r+b");
		fread(&count,sizeof(int),1,f1);
		table = Init(10);
		Readfromfile(table,f1,f2,count);
	}
        do{
                flag = Menu(menu,6,table,f1,f2);
        }while (flag < 6 && flag > 0);
	    fseek(f1,0,SEEK_SET);
	    fwrite(&table->n,sizeof(int),1,f1);
	    fclose(f1);
        fclose(f2);
        Clear(table);
        return 1;
}
