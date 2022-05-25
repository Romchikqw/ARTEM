#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
typedef struct Keyspace {
        int key;
        char *info;
        struct Keyspace *next;
}Keyspace;

typedef struct Table{
        int csize;
        int msize;
        struct Keyspace *ks1;
}Table;

#endif
