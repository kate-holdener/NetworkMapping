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
         individuals[i]->m_solution.valid_nodes_ratio() * 
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

void node_balance_sum(Individual **individuals, int num_individuals)
{
   for (int i = 0; i < num_individuals; i++)
   {
      individuals[i]->m_fitness = individuals[i]->m_solution.node_balance_ratio_sum();
   }
}

void feasible_node_balance_sum(Individual **individuals, int num_individuals)
{
   nodes_and_links_ratio(individuals, num_individuals);
   for (int i = 0; i < num_individuals; i++)
   {
      if (individuals[i]->m_fitness == 1)
      {
         individuals[i]->m_feasible = 1;
         printf("Found feasible solution\n");
      }
      else
      {
         individuals[i]->m_feasible = 0;
      }
      individuals[i]->m_fitness*= individuals[i]->m_solution.node_balance_ratio_sum()/individuals[i]->m_solution.get_from_size();
   }
 
}
}
