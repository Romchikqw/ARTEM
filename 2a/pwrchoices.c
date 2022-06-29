#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#include "pwrchoices.h"


void entry_pwrchoices(Quene* first_quene, Quene* second_quene, Passenger* passenger) {
    size_t first_quene_size = first_quene->quene_size;
    size_t second_quene_size = second_quene->quene_size;

    _Bool flag = first_quene_size <= second_quene_size ? true : false;

    if (flag == true)
        quene_entry(first_quene, passenger);
    else
        quene_entry(second_quene, passenger);
    
}
