/*
 * Various fitness functions that could be plugged into the EA
 */

#ifndef FITNESS_H
#define FITNESS_H

#include "Individual.h"

extern "C"
{

/*
 * This fitness function calculates:
 * (# nodes that satisfy constraints/ total number of nodes) +
 * (# of links that satisfy constraints / total number of links)
 * Maximum fitness value under this function is 2
 */
void nodes_and_links_ratio(Individual **individuals, int num_individuals);

void nodes_ratio(Individual **individuals, int num_individuals);

void links_ratio(Individual **individuals, int num_individuals);
}

#endif
