#ifndef RECEPTION_UTILS_H
#define RECEPTION_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "struct.h"
#include "passenger.h"
#include "pwrchoices.h"


typedef struct Reception {
    int tp; // time has passed

    Quene* first_quene;
    Quene* second_quene;
} Reception;

Reception* reception_init(size_t participant_num);
static void _status_quene(Quene* quene, int tp);
static void _reception_print(Reception* reception, int tp);
void reception_main();

#endif /* RECEPTION_UTILS */
