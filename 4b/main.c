#include <stdio.h>
#include "q-tree.h"

int main(){
    QTree* qtree = qtree_create();

    qtree_add_value(qtree, "aaa\0", "111\0", 1);

    printf("=====================================\n");
    qtree_show(qtree, NULL, NULL);
    printf("=====================================\n");

    qtree_add_value(qtree, "bbb\0", "212\0", 2);

    printf("=====================================\n");
    qtree_show(qtree, NULL, NULL);
    printf("=====================================\n");

    qtree_add_value(qtree, "ccc\0", "333\0", 3);

    printf("=====================================\n");
    qtree_show(qtree, NULL, NULL);
    printf("=====================================\n");

    qtree_add_value(qtree, "ddd\0", "444\0", 4);
    qtree_add_value(qtree, "aaa\0", "555\0", 2);
    qtree_add_value(qtree, "aaa\0", "111\0", 3);

    printf("=====================================\n");
    qtree_show(qtree, NULL, NULL);
    printf("=====================================\n");


    printf("+++++++++++++Find testing+++++++++++++++++\n");
    PtrList* found_list = NULL;
    int found_n = qtree_find(qtree, &found_list, "aaa\0", "111\0");
    printf("Found list with %d elements:\n", found_n);
    ptrlist_show_values(found_list);
    ptrlist_delete(found_list);

    printf("+++++++++++++Remove testing+++++++++++++++++\n");

    printf("=====================================\n");
    qtree_show(qtree, NULL, NULL);
    printf("=====================================\n");


    qtree_remove_value(qtree, "aaa\0", "111\0");
    found_list = NULL;
    found_n = qtree_find(qtree, &found_list, "aaa\0", "111\0");
    printf("Found list with %d elements:\n", found_n);
    ptrlist_show_values(found_list);
    ptrlist_delete(found_list);

    printf("=====================================\n");
    qtree_show(qtree, NULL, NULL);
    printf("=====================================\n");


    qtree_delete(qtree);
    return 0;
}
