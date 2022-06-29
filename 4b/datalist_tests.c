#include <stdio.h>
#include <stdlib.h>
#include "q-tree.h"

int main(){
DataList* list = datalist_create();
    printf("List created:\n");

    printf("Insert data: %s, %s, %d\n", "aaa", "111", 2);
    datalist_insert(list, "aaa\0", "111\0", 2);
    
    printf("---\n");
    datalist_show(list);
    printf("---\n");

    printf("Insert data: %s, %s, %d\n", "bbb", "222", 3);
    datalist_insert(list, "bbb\0", "222\0", 3);
    
    printf("---\n");
    datalist_show(list);
    printf("---\n");

    printf("Insert data: %s, %s, %d\n", "ccc", "333", 4);
    datalist_insert(list, "ccc\0", "333\0", 4);
    
    printf("---\n");
    datalist_show(list);
    printf("---\n");

    printf("Insert data: %s, %s, %d\n", "ccc", "333", 4);
    datalist_insert(list, "ccc\0", "333\0", 4);
    
    printf("---\n");
    datalist_show(list);
    printf("---\n");

    printf("Insert data: %s, %s, %d\n", "ddd", "444", 5);
    datalist_insert(list, "ddd\0", "444\0", 5);
    
    printf("---\n");
    datalist_show(list);
    printf("---\n");


    printf("+++++++++++++Find testing+++++++++++++++++\n");
    PtrList* found_list = NULL;
    int found_n = datalist_find(list, &found_list, "ccc\0", "333\0");
    printf("Found list with %d elements:\n", found_n);
    ptrlist_show_values(found_list);
    ptrlist_delete(found_list);

    printf("---\n");
    datalist_show(list);
    printf("---\n");

    printf("+++++++++++++Find k testing+++++++++++++++++\n");
    found_list = NULL;
    found_n = datalist_find_k(list, &found_list, "bbb\0", "222\0");
    printf("Found list with %d elements:\n", found_n);
    ptrlist_show_values(found_list);
    ptrlist_delete(found_list);

    printf("---\n");
    datalist_show(list);
    printf("---\n");

    printf("+++++++++++++Delete testing+++++++++++++++++\n");
    datalist_remove(list, "ccc\0", "333\0");
    printf("---\n");
    datalist_show(list);
    printf("---\n");

    printf("+++++++++++++Show k testing+++++++++++++++++\n");
    datalist_show_k(list, "qqq\0", "777\0");

    datalist_delete(list);
    printf("List deleted.\n");
	return 0;
}
