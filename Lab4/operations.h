#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "header.h"

item *init(int key,char* info);
int get_thread(item *temp);
int insert(item *root,int key,char *info);
item *search(item *root,int key);
item *min(item *root);
item *search_max(item *root,int key);
int delete(item *root,int key);
void print(item *root);
int clear(item *root);

#endif

