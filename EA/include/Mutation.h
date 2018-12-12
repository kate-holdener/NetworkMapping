/*
 * Various mutation functions that could be plugged into the EA
 */

#ifndef MUTATION_H
#define MUTATION_H

#include "Individual.h"

extern "C"
{
void mutate_random(Individual *individual, float mutation_rate);
}
#endif

