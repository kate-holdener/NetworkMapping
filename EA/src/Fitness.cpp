/*
 * Various fitness functions that could be plugged into the EA
 */

#include "Fitness.h"
extern "C"
{
void nodes_and_links_ratio(Individual **individuals, int num_individuals)
{
   for (int i = 0; i < num_individuals; i++)
   {
      individuals[i]->m_fitness =  
         individuals[i]->m_solution.valid_nodes_ratio() + 
         individuals[i]->m_solution.valid_links_ratio();
   }
}

void nodes_ratio(Individual **individuals, int num_individuals)
{
   for (int i = 0; i < num_individuals; i++)
   {
      individuals[i]->m_fitness =  
         individuals[i]->m_solution.valid_nodes_ratio(); 
   }
}

void links_ratio(Individual **individuals, int num_individuals)
{
   for (int i = 0; i < num_individuals; i++)
   {
      individuals[i]->m_fitness =  
         individuals[i]->m_solution.valid_links_ratio(); 
   }
}
}
