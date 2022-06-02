#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Header.h"

Table *Init(int count);
void Createelfromfile(Table *table,int takeoff,FILE *f2);
int Readfromfile(Table *table,FILE *f1,FILE *f2,int count);
char *Find(Table *table,int key);
int Add(Table *table,int key,char *info);
int AddforTable(Table *table,int key,char *info);
int AddforFile(Table *table,int key,char *info,FILE *f1,FILE *f2);
int Delete(Table *table , int key,FILE *f1,FILE *f2);
int Print(Table *table);
int Clear(Table *table);
void Roma(Table *table,int a,int b);

#endif
