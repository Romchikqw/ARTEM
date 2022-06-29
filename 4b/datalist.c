#include <stdio.h>
#include <stdlib.h>
#include "q-tree.h"

DataList* datalist_create(){
    DataList* new_datalist = malloc(sizeof(DataList));
    new_datalist->key_1 = NULL;
    new_datalist->key_2 = NULL;
    new_datalist->value = -1;
    new_datalist->next = NULL;
    return new_datalist;
}

DataNode* datalist_create_data_node(char* key_1, char* key_2, uint value){
    DataNode* new_datanode = malloc(sizeof(DataNode));
    new_datanode->key_1 = key_1;
    new_datanode->key_2 = key_2;
    new_datanode->value = value;
    new_datanode->next = NULL;
    return new_datanode;
}

int cmp_keys(const char* left, const char* right){
    if(!left && !right){
        return 0;
    } else if (!left){
        return 1;
    } else if (!right){
        return (-1);
    }

    char l = left[0];
    char r = right[0];
    uint i = 1;
    while (l != '\0' && r == l){
        l = left[i];
        r = right[i];
        i++;
    }
    return (int)l - (int)r; 
}

int leq_data(const DataNode* left, const DataNode* right){ //less or equal
    if(!left && !right){
        return 1;
    }
    if (!left){
        return 0;
    }
    if (!right){
        return 1;
    }
    int k1 = cmp_keys(left->key_1, right->key_1);
    if (!k1){
        return cmp_keys(left->key_2, right->key_2) <= 0 ;
    }
    return k1 <= 0;
}

void datalist_append_node(DataList* datalist, DataNode* datanode){
    if (!datalist || !datanode){
        fprintf(stderr, "Nothing to append!\n");
        return ;
    }
    DataNode* last_node = datalist;
    while(last_node->next){
        printf("While loop\n");
        last_node = last_node->next;
    }
    last_node->next = datanode;
}

void datalist_insert(DataList* datalist, char* key_1, char* key_2, uint value){
    if (!datalist){
        return ;
    }
    DataNode* new_node = datalist_create_data_node(key_1, key_2, value);
    DataNode* curr_node = datalist;
    while (curr_node->next && leq_data(curr_node->next, new_node)){
        curr_node = curr_node->next;
    }
    if (!curr_node->next){
        datalist_append_node(curr_node, new_node);
        return ;
    }
    new_node->next = curr_node->next;
    curr_node->next = new_node;
}

DataList* datalist_find_node_next(DataList* datalist, DataNode* datanode){
    if (!datalist || !datalist->next || !datanode){
        printf("Ret NULL\n");
        return NULL;
    }
    if (!cmp_keys(datalist->next->key_1, datanode->key_1) && !cmp_keys(datalist->next->key_2, datanode->key_2)){
        return datalist;
    }
    return datalist_find_node_next(datalist->next, datanode);
}

DataList* datalist_find_node(DataList* datalist, DataNode* datanode){
    DataNode* found_node = datalist_find_node_next(datalist, datanode);
    return  found_node ? found_node->next : NULL;
}

void datalist_delete_node(DataNode* datanode){
    if (!datanode){
        return;
    }
    datanode->value = 0;
    datanode->next = NULL;
    free(datanode);
}

int datalist_find(DataList* datalist, PtrList** found, char* key_1, char* key_2){
    if (!datalist && !found){
        return (-1);
    }
    int num_found = 0;

    ptrlist_delete(*found);
    *found = ptrlist_create();
    DataNode* found_node = NULL;
    DataNode* needed_node = datalist_create_data_node(key_1, key_2, -1);
    found_node = datalist_find_node(datalist, needed_node);

    while(found_node){
        printf("Searching while loop\n");
        num_found++;
        ptrlist_append(*found, found_node);

        found_node = datalist_find_node(found_node, needed_node);
    }
    datalist_delete_node(needed_node);
    return num_found;
}

int datalist_find_k(DataList* datalist, PtrList** found, char* key_1, char* key_2){
    if (!datalist && !found){
        return (-1);
    }
    int num_found = 0;

    ptrlist_delete(*found);
    *found = ptrlist_create();
    DataNode* found_node = NULL;

    DataNode* pivot_node = datalist_create_data_node(key_1, key_2, -1);
    DataNode* curr_node = datalist;
    while (curr_node->next && leq_data(curr_node->next, pivot_node)){
        num_found++;
        ptrlist_append(*found, curr_node->next);
        curr_node = curr_node->next;
    }
    datalist_delete_node(pivot_node);
    return num_found;
}

void datalist_split(DataList* datalist, DataList** splitted, char** key_pivots){
    if (!datalist && !splitted){
        return ;
    }
    int num_found = 0;
    
    int k1_cmp = 0;
    int k2_cmp = 0;
    for(int i = 0; i < 4; ++i){
        splitted[i] = datalist_create();
    }
    DataNode* curr_node = datalist->next;
    while (curr_node){
        datalist->next = datalist->next->next;
        curr_node->next = NULL;

        k1_cmp = cmp_keys( curr_node->key_1, key_pivots[0]);
        k2_cmp = cmp_keys(curr_node->key_2, key_pivots[1]);
        if (k1_cmp <= 0){
            if (k2_cmp <=0){
                datalist_append_node(splitted[0], curr_node);
            } else{
                datalist_append_node(splitted[1], curr_node);
            }
        } else{
            if (k2_cmp <=0){
                datalist_append_node(splitted[2], curr_node);
            } else{
                datalist_append_node(splitted[3], curr_node);;
            }
        }
        curr_node = datalist->next;
    }
}

int datalist_find_next(DataList* datalist, PtrList** found, char* key_1, char* key_2){
    if (!datalist && !*found){
        return (-1);
    }
    int num_found = 0;

    datalist_delete(*found);
    *found = ptrlist_create();
    DataNode* found_node = NULL;
    DataNode* needed_node = datalist_create_data_node(key_1, key_2, -1);
    found_node = datalist_find_node_next(datalist, needed_node);
    while(found_node){
        num_found++;
        ptrlist_append(*found, found_node);
        printf("-+-\n");
        printf("Del Found k1: %s\n", found_node->key_1);
        printf("Del Found k1 - next: %s\n", found_node->next->key_1);
        printf("-+-\n");
        found_node = datalist_find_node_next(found_node->next, needed_node);
    }
    datalist_delete_node(needed_node);
    return num_found;
}

void datalist_remove(DataList* datalist, char* key_1, char* key_2){
    if (!datalist){
        return ;
    }
    PtrList* nodes_to_remove = datalist_create();
    int num_to_remove;


    num_to_remove = datalist_find_next(datalist, &nodes_to_remove, key_1, key_2);

    PtrNode* curr_node = nodes_to_remove->next;
    while (curr_node->next){
        curr_node = curr_node->next;
    }
    for(int i = num_to_remove - 1; i >=0; --i){
        DataNode* tmp = curr_node->ptr->next;
        curr_node->ptr->next = curr_node->ptr->next->next;
        datalist_delete_node(tmp);
        curr_node = curr_node->prev;
    }
    ptrlist_delete(nodes_to_remove);
}

void datalist_remove_oldest(DataList* datalist, char* key_1, char* key_2){
    if (!datalist){
        return ;
    }
    PtrList* nodes_to_remove = datalist_create();
    int num_to_remove;


    num_to_remove = datalist_find_next(datalist, &nodes_to_remove, key_1, key_2);

    PtrNode* curr_node = nodes_to_remove->next;
    DataNode* tmp = curr_node->ptr->next;
    curr_node->ptr->next = curr_node->ptr->next->next;
    datalist_delete_node(tmp);
    ptrlist_delete(nodes_to_remove);
}

void datalist_delete(DataList* datalist){
    if (!datalist){
        return ;
    }
    if (datalist->next){
        datalist_delete(datalist->next);
    }
    datalist_delete_node(datalist);
}

void datalist_show_k(DataList* datalist, char* key_1, char* key_2){
    if (!datalist){
        return ;
    }
    DataNode* pivot_node = datalist_create_data_node(key_1, key_2, -1);
    DataNode* curr_node = datalist;
    while (curr_node->next && leq_data(curr_node->next, pivot_node)){
        printf("[[k1: %s - k2: %s - v: %u]]->\n",
               curr_node->next->key_1,
               curr_node->next->key_2,
               curr_node->next->value);
        curr_node = curr_node->next;
    }
    datalist_delete_node(pivot_node);
}

PtrNode* ptrlist_create_ptr_node(DataNode* ptr){
    PtrNode* new_ptrnode = malloc(sizeof(DataNode));
    new_ptrnode->ptr = ptr;
    new_ptrnode->next = NULL;
    new_ptrnode->prev = NULL;
    return new_ptrnode;
}

void datalist_show(DataList* datalist){
    datalist_show_k(datalist, NULL, NULL);
}

PtrList* ptrlist_create(){
    PtrList* new_ptrlist = malloc(sizeof(PtrList));
    new_ptrlist->ptr = NULL;
    new_ptrlist->next = NULL;
    new_ptrlist->prev = NULL;
    return new_ptrlist;
}

void ptrlist_append(PtrList* ptrlist, DataNode* ptr){
    if (!ptrlist){
        return ;
    }
    PtrNode* new_node = ptrlist_create_ptr_node(ptr);
    PtrNode* curr_node = ptrlist;
    while (curr_node->next){
        curr_node = curr_node->next;
    }
    curr_node->next = new_node;
    new_node->prev = curr_node;
}

int datalist_len(DataList* datalist){
    if (!datalist){
        return ;
    }
    DataNode* curr_node = datalist;
    int len = 0;
    while (curr_node->next){
        curr_node = curr_node->next;
        ++len;
    }
    return len;
}

void ptrlist_delete_node(PtrNode* ptrnode){
    if (!ptrnode){
        return ;
    }
    ptrnode->ptr = NULL;
    ptrnode->next = NULL;
    ptrnode->prev = NULL;
    free(ptrnode);
}

void ptrlist_delete(PtrList* ptrlist){
    if (!ptrlist){
        return ;
    }
    if (ptrlist->next){
        ptrlist_delete(ptrlist->next);
    }
    ptrlist_delete_node(ptrlist);
}

void ptrlist_show_values(PtrList* ptrlist){
    if (!ptrlist){
        return ;
    }
    PtrNode* curr_node = ptrlist;
    while (curr_node->next){
        if (curr_node->next->ptr){
            printf("*[[k1: %s - k2: %s - v: %u]]->\n",
            curr_node->next->ptr->key_1,
            curr_node->next->ptr->key_2,
            curr_node->next->ptr->value);
        }
        curr_node = curr_node->next;
    }
}
