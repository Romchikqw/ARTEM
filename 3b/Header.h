#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>

typedef	struct Keyspace{
	int key;
	char *info;
	struct Keyspace *next;
}Keyspace;

typedef struct Table{
	int n;
        int count;
        FILE *fd;
        struct Keyspace *ks1;
}Table;

#endif





