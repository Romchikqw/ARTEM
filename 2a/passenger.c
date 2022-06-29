#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "passenger.h"


Passenger* passenger_init(size_t id, unsigned int ta, unsigned int ts) {
    Passenger* passenger = (Passenger*)calloc(1, sizeof(passenger));

    passenger->id = id;
    passenger->ta = ta;
    passenger->ts = ts;
    passenger->tw = 0;

    return passenger;
}
