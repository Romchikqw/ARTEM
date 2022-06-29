#ifndef DATALIST_H
# define DATALIST_H
typedef unsigned int uint;

typedef struct data_list_node_ {
  char* key_1;
  char* key_2;
  uint value;

  struct data_list_node_*  next;
} DataList;

typedef DataList DataNode;

typedef struct ptr_list_node_ {
  DataNode* ptr;
  struct ptr_list_node_*  next;
  struct ptr_list_node_*  prev;
} PtrList;

typedef PtrList PtrNode;

DataList* datalist_create();

void datalist_insert(DataList* datalist, char* key_1, char* key_2, uint value);

int datalist_find(DataList* datalist, PtrList** found, char* key_1, char* key_2);

int datalist_find_k(DataList* datalist, PtrList** found, char* key_1, char* key_2);

void datalist_remove(DataList* datalist, char* key_1, char* key_2);

void datalist_remove_oldest(DataList* datalist, char* key_1, char* key_2);

void datalist_delete(DataList* datalist);

void datalist_show(DataList* datalist);

void datalist_show_k(DataList* datalist, char* key_1, char* key_2);

int cmp_keys(const char* left, const char* right);

void datalist_split(DataList* datalist, DataList** splitted, char** key_pivots);

int datalist_len(DataList* datalist);


PtrList* ptrlist_create();

void ptrlist_append(PtrList* ptrlist, DataNode* ptr);

// int ptrlist_find(PtrList* ptrlist, PtrList** found, char* key_1, char* key_2);

// void ptrlist_remove(PtrList* ptrlist, DataNode* ptr);

void ptrlist_delete(PtrList* ptrlist);

void ptrlist_show_values(PtrList* ptrlist);

// void ptrlist_show_k(PtrList* ptrlist, char* key_1, char* key_2);

// int cmp_keys(char* left, char* right);

#endif //DATALIST_H
