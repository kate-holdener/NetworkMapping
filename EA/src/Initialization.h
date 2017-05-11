/*
 *  A collection of initialization functions that could be plugged into an EA
 */
#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "Individual.h"
extern "C"
{
/*
 * Initializes population at random
 */
void initialize_random(Individual *individual);
}

#endif
