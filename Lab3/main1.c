#include "choose.h"
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int Menu(const char *menu[],int a,Table *table){
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
			if (CheckSize(table)){
				printf("The table is filled in\n");
				return 1;
				break;
			}
			printf("Insert your key\n");
			scanf("%d",&key);
			if (Find(table,key )){
				printf("The key already exist\n");
			}
			else{
				printf("Insert your info\n");
                                char *info = (char *)calloc(25,sizeof(char));
				scanf("%s",info);
				Add(table,key,info);
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
                        else Delete(table,key);
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

	printf("Enter the size of table:\n");
	scanf("%d",&count);
//	printf("\n");
	while (count == 0){
		printf("Введите другого значение!\n");
		scanf("%d",&count);
	}
	Table *table = Init(count);
	do{
		flag = Menu(menu,6,table);
	}while (flag < 6 && flag > 0);
	Clear(table);
	return 1;
}
