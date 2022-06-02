#ifndef HEADER_H
#define HEADER_H

typedef struct item{
    unsigned int key;
    char* info;
    struct item *left;
    struct item *right;
    struct item *parent;
    struct item *threaded;
}item;


#endif



