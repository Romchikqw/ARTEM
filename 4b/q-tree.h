#ifndef Q_TREE_H
# define Q_TREE_H

#include "datalist.h"
# define NODE_MAX_VALUES 1
//# define KEY_SPACE_SIZE 128


typedef unsigned int uint;

typedef struct q_node_ {
  DataList* data;
  uint data_num;

  char* key_1_pivot;
  char* key_2_pivot;

  struct q_node_**  subtrees;
} QTree;

typedef QTree QTreeNode;

QTree* qtree_create();

void qtree_delete(QTree* qtree);

void qtree_add_value(QTree* qtree, char* key_1, char* key_2, uint value);

void qtree_remove_value(QTree* qtree, char* key_1, char* key_2);

int qtree_find(QTree* qtree, PtrList** found, char* key_1, char* key_2);

void qtree_show(QTree* qtree, char* key_1, char* key_2);

#endif // Q_TREE_H
