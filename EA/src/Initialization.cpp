/*
 * Various initialization operators that could be plugged into an EA.
 */

#include "Initialization.h"
#include <stdlib.h>
extern "C"
{

void initialize_random(Individual *individual)
{
   int num_nodes_from = individual->m_solution.get_from_size();
   int num_nodes_to   = individual->m_solution.get_to_size();

   for (int i = 0; i < num_nodes_from; i++)
   {
      individual->m_solution.m_mapping[i] = rand() % num_nodes_to;
   }
}

}
