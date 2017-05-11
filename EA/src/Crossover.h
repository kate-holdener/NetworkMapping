/*
 *  Various crossover operators that could be plugged into an EA
 */

#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "Population.h"
extern "C"
{
void crossover_random(Population *population);

void crossover_two_point(Population *population);

}
#endif

