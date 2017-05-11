#ifndef SELECTION_H
#define SELECTION_H

#include "Population.h"
extern "C"
{
void roulette_wheel(Population *population);

void rank(Population *population);

}
#endif
