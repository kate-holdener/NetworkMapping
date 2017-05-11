/*
 * Various mutation functions that could be plugged into the EA
 */

#include "Mutation.h"
#include <stdlib.h>

extern "C"
{

void mutate_random(Individual *individual, float mutation_rate)
{
   static int num_mutated_genes = 0;
   int mutation_point;
   // pick mutation point
   int from_size = individual->m_solution.get_from_size();
   int to_size = individual->m_solution.get_to_size();
   for (int i = 0; i < from_size; i++)
   {
      if ((rand() % 1000)/1000.0 < mutation_rate)
      {
         individual->m_solution.m_mapping[i] = rand() % 
            individual->m_solution.get_to_size();
         num_mutated_genes++;
      }
   }
   if (num_mutated_genes & 0xFF == 0)
   {
      printf("mutated %u genes\n", num_mutated_genes);
   }
}

}

