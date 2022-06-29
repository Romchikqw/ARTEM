#ifndef PASSANGER_H
#define PASSANGER_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Passenger {
    size_t id;
    int ta; // arrival time
    int ts; // service time
    int tw; // wait time
} Passenger;


Passenger* passenger_init(size_t id, unsigned int ta, unsigned int ts);

#endif /* PASSANGER_H */
