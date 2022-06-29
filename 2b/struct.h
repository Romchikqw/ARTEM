#ifndef QUENE_H
#define QUENE_H

#include <stdio.h>
#include <stdbool.h>


typedef struct Quene {
    void** data;
    size_t data_size;
    size_t quene_size;

    size_t head;
    size_t tail;

    _Bool empty;
    _Bool full;
} Quene;


Quene* quene_init(size_t data_size);
void quene_entry(Quene* quene, void* item);
void* quene_read(Quene* quene);
void quene_state(Quene* quene);

#endif
