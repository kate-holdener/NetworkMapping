/*
 * Various competition functions that could be plugged into the EA 
 */

#ifndef COMPETITION_H
#define COMPETITION_H

#include "Population.h"
extern "C"
{

/*
 * Select the best N individuals among the pool of all parents 
 * and all offspring. N is population_size.
 */
void fittest_survive(Population *population);

/*
 * All offspring replace all parents
 * Number of offspring must equal number of parents
 */
void replace(Population *population);


/*
 * The least fit 50% of parents are replaced by the most fit offspring
 */
void replace_half(Population *population);
}
#endif
