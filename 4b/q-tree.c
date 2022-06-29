#include <stdio.h>
#include <stdlib.h>
#include "q-tree.h"

QTree* qtree_create(){
    QTree* new_tree = malloc(sizeof(QTree));
    new_tree->data = datalist_create();
    new_tree->key_1_pivot = NULL;
    new_tree->key_2_pivot = NULL;
    new_tree->data_num = 0;
    new_tree->subtrees = NULL;
    return new_tree;
}

QTreeNode* qtree_create_node(DataList* data, int data_num){
    QTreeNode* new_node = malloc(sizeof(QTreeNode));
    new_node->data = data;
    new_node->key_1_pivot = NULL;
    new_node->key_2_pivot = NULL;
    new_node->data_num = data_num;
    new_node->subtrees = NULL;
    return new_node;
}

void qtree_delete(QTree* qtree){
    if (!qtree){ 
        return;
    }
    else if (qtree->subtrees){
        for(int i = 0; i < 4; ++i){
            qtree_delete(qtree->subtrees[i]);
        }
        free(qtree->subtrees);
    }
    datalist_delete(qtree->data);
    qtree->data_num = 0;
    if (qtree->key_1_pivot){
            free(qtree->key_1_pivot);
        }
    if (qtree->key_2_pivot){
            free(qtree->key_2_pivot);
        }
    free(qtree);
}

void split_tree_node(QTreeNode* qnode){
    char** key_pivots[2];
    get_key_pivots(qnode->data, qnode->data_num, key_pivots);
    DataList** splitted[4];
    datalist_split(qnode->data, splitted, key_pivots);

    qnode->key_1_pivot = key_pivots[0];
    qnode->key_2_pivot = key_pivots[1];

    qnode->subtrees = malloc(sizeof(QTreeNode*)*4);

    int new_data_num = 0;
    for(int i = 0; i < 4; ++i){
        new_data_num = datalist_len(splitted[i]);
        qnode->subtrees[i] = qtree_create_node(splitted[i], new_data_num);
        datalist_delete(qnode->data);
        qnode->data = NULL;
        qnode->data_num = 0;
    } 
}

int find_node_next(QTree* qtree, QTreeNode** found, char* key_1, char* key_2){
    if (!qtree || !found){
        return;
    }
    QTreeNode* prev_node = NULL;
    QTreeNode* curr_node = qtree;
    int curr_node_idx = -1;
    int k1_cmp = 0;
    int k2_cmp = 0;
    while (curr_node->subtrees){
        k1_cmp = cmp_keys(key_1, curr_node->key_1_pivot);
        k2_cmp = cmp_keys(key_2, curr_node->key_2_pivot);
        prev_node = curr_node;
        if (k1_cmp <= 0){
            if (k2_cmp <=0){
                curr_node = curr_node->subtrees[0];
                curr_node_idx = 0;
            } else{
                curr_node = curr_node->subtrees[1];
                curr_node_idx = 1;
            }
        } else{
            if (k2_cmp <=0){
                curr_node = curr_node->subtrees[2];
                curr_node_idx = 2;
            } else{
                curr_node = curr_node->subtrees[3];
                curr_node_idx = 3;
            }
        }
    }
    if (!*found){
        qtree_delete(*found);
    }
    *found = prev_node;
    return curr_node_idx;
} 

QTreeNode* qtree_find_node(QTree* qtree, char* key_1, char* key_2){
    QTreeNode* found = NULL;
    int found_idx = -1;
    found_idx = find_node_next(qtree, &found, key_1, key_2);
    if (found_idx < 0){
        return qtree;
    }
    return found->subtrees[found_idx];
}

void qtree_add_value(QTree* qtree, char* key_1, char* key_2, uint value){
    if (!qtree){
        return;
    }
    QTreeNode* found = NULL;
    found = qtree_find_node(qtree, key_1, key_2);
    int k1_cmp = 0;
    int k2_cmp = 0;
    if (found->data_num + 1 > NODE_MAX_VALUES){
        split_tree_node(found);

        k1_cmp = cmp_keys(key_1, found->key_1_pivot);
        k2_cmp = cmp_keys(key_2, found->key_2_pivot);
        if (k1_cmp <= 0){
            if (k2_cmp <=0){
                found = found->subtrees[0];
            } else{
                found = found->subtrees[1];
            }
        } else{
            if (k2_cmp <=0){
                found = found->subtrees[2];
            } else{
                found = found->subtrees[3];
            }
        }
    }
    
    found->data_num++;
    datalist_insert(found->data, key_1, key_2, value);
}

char* key_copy(const char* key){
    int i = 0;
    while(key[i] != '\0'){
        ++i;
    }
    char* copy = malloc(sizeof(char)*(i+2)); // i = size-1 ; i +2 = size + '\0'
    i = 0;
    while(key[i] != '\0'){
        copy[i] = key[i];
        ++i;
    }
    copy[i] = key[i];
    return copy;
}

void get_key_pivots(DataList* datalist, int num_data, char** key_pivots){
    if (!datalist || !key_pivots){
        return;
    }
    DataNode* curr_node = datalist->next;
    int i = 0;
    while (curr_node){
        if (i == (int)(num_data/2)){
            key_pivots[0] = key_copy(curr_node->key_1);
            key_pivots[1] = key_copy(curr_node->key_2);
            return;
        }
        i++;
        curr_node = curr_node->next;
    }
}


int qtree_find(QTree* qtree, PtrList** found, char* key_1, char* key_2){
    // printf("[DEBUG]:Qtree - Searching begin\n");
    //if (!qtree){
    //    return;
    //}
    QTreeNode* qtree_found = NULL;
    qtree_found = qtree_find_node(qtree, key_1, key_2);
    // printf("Found data:\n");
    // datalist_show(qtree_found->data);
    // printf("[DEBUG]:Qtree - Searching success\n");
    return datalist_find(qtree_found->data, found, key_1, key_2);
}

void qtree_remove_value(QTree* qtree, char* key_1, char* key_2){
    // printf("[DEBUG]:Qtree - removing begin\n");
    if (!qtree){
        return;
    }
    QTreeNode* qtree_found = NULL;
    qtree_found = qtree_find_node(qtree, key_1, key_2);
    // printf("Found data:\n");
    // datalist_show(qtree_found->data);

    datalist_remove_oldest(qtree_found->data, key_1, key_2);
    qtree_found->data_num--;
}

void qtree_show(QTree* qtree, char* key_1, char* key_2){
    if (!qtree){
        return;
    }
    if(qtree->subtrees){
        for(int i = 0; i < 4;++i){
            qtree_show(qtree->subtrees[i], key_1, key_2);
        }
    }
    if (!qtree->subtrees){
        // printf("New leaf node\n");
        datalist_show_k(qtree->data, key_1, key_2);
    }

}
