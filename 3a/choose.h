#ifndef CHOOSE_H
#define CHOOSE_H
#include "header.h"

Table *Init(int count);
int CheckSize(Table *table);
char *Find(Table *table,int key);
int Add(Table *table,int key,char *info);
int Delete(Table *table , int key);
int Print(Table *table);
int Clear(Table *table);
void Roma(Table *table,int a,int b);

#endif
