#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "on_list.h"



Quene* quene_init(size_t data_size) {
    Quene* quene = (Quene*)calloc(1, sizeof(Quene));
    quene->data_size = data_size;

    quene->head = 0;
    quene->tail = 0;

    quene->empty = true;
    quene->full = false;

    quene->data = (void**)calloc(1, sizeof(Node*));

    return quene;
}



void quene_entry(Quene* quene, void* item) {
    size_t head_index = quene->head % quene->data_size;
    size_t tail_index = quene->tail % quene->data_size;

    if (quene->full != true) {
        push(((Node**)quene->data), item);
        ++quene->tail;
        ++quene->quene_size;

        ++tail_index;
        tail_index %= quene->data_size;

        if (quene->empty == true)
            quene->empty = false;
        
        if (head_index == tail_index) {
            quene->full = true;
        }
    }
}



void* quene_read(Quene* quene) {
    size_t head_index = quene->head % quene->data_size;
    size_t tail_index = quene->tail % quene->data_size;
    void* quene_head = NULL;

    if (quene->empty == false) {
        quene_head = pop_back((Node**)quene->data);
        ++quene->head;
        --quene->quene_size;

        ++head_index;
        head_index %= quene->data_size;

        if (head_index % quene->data_size == tail_index)
            quene->empty = true;

        if (head_index % quene->data_size != tail_index)
            quene->full = false;
    }

    return quene_head;

}



void quene_state(Quene* quene) {
    printf("Quene: {");
    printf("head: %zu, tail: %zu\n", quene->head, quene->tail);
    printf("        empty: %d, full: %d};\n", quene->empty, quene->full);
    
}
