#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "reception.h"


Reception* reception_init(size_t participant_num) {
    Reception* reception = (Reception*)calloc(1, sizeof(Reception));
    reception->tp = 0;
    
    reception->first_quene = quene_init(participant_num);
    reception->second_quene = quene_init(participant_num);

    return reception;
}


Quene* read_passengers(size_t passengers_num) {
    Quene* passengers = quene_init(passengers_num);
    int ta;
    int ts;

    
    for (size_t id = 1; id < passengers_num+1; ++id) {
        printf("Passenger [%zu]: \n", id);
        printf("arrival time: ");
        scanf("%d", &ta);
        printf("service time: ");
        scanf("%d", &ts);
        quene_entry(passengers, passenger_init(id, ta, ts));
    }
    return passengers;
}



void reception_main() {
    int tp = 0;
    size_t passengers_num;
    printf("Enter passengers num: ");
    scanf("%zu", &passengers_num);
    Quene* passengers = read_passengers(passengers_num);

    Reception* reception = reception_init(passengers_num);

    Quene* first_quene = reception->first_quene;
    Quene* second_quene = reception->second_quene;

    while ((first_quene->empty != true)  ||
           (second_quene->empty != true) ||
           (passengers->empty != true)) {

        if ((passengers->empty != true) &&
           (((Passenger*)passengers->data[passengers->head])->ta == tp)) {
            entry_pwrchoices(first_quene, second_quene,
                             passengers->data[passengers->head]);
            quene_read(passengers);
        }
        
        _status_quene(first_quene, tp);
        _status_quene(second_quene, tp);
        _reception_print(reception, tp);
        tp++;
    }
    free(passengers);
    free(reception);
}



static void _status_quene(Quene* quene, int tp) {
    Passenger* passenger = quene->data[quene->head];
    if (passenger != NULL) {
        ++passenger->tw;
        if (passenger->tw == passenger->ts)
            quene_read(quene);
    }
}


static void _reception_print(Reception* reception, int tp) {
    size_t id;

    size_t first_quene_head = reception->first_quene->head;
    size_t second_quene_head = reception->second_quene->head;

    size_t first_quene_tail = reception->first_quene->tail;
    size_t second_quene_tail = reception->second_quene->tail;
    
    printf("\n\n");
    printf("Time reception [%hu]:\n", tp);
    printf("\tfirst quene: ");
    for (size_t i = first_quene_head; i < first_quene_tail; ++i) {
        id = ((Passenger*)reception->first_quene->data[i])->id;
        printf("%zu ", id);
    }
    printf("\n");
    printf("\tsecond quene: "); 
    for (size_t i = second_quene_head; i < second_quene_tail; ++i) {
        id = ((Passenger*)reception->second_quene->data[i])->id;
        printf("%zu ", id);
    }
    printf("\n");


    printf("\n\n");
}

