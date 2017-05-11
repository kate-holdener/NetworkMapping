/*
 *  Various crossover operators that could be plugged into an EA
 */

#include "Crossover.h"
#include <string.h>

extern "C"
{

void crossover_random(Population *population)
{
   int next_offspring = 0;
   int num_parents    = population->m_num_parents;
   int num_pairs      = num_parents/2;
   int solution_size  = population->m_parents[0]->m_solution.get_from_size();
   int p = 0;
   for (int i = 0; i < num_pairs; i++)
   {
      Individual *parent1 = population->m_selected_parents[p++];
      Individual *parent2 = population->m_selected_parents[p++];
 
      int crossover_point = rand() % solution_size;
      if (crossover_point == 0)
      {
         crossover_point = 1;
      }
    
      // offspring 1
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping, 
             parent1->m_solution.m_mapping, sizeof(int)*crossover_point);
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping+crossover_point,
             parent2->m_solution.m_mapping+crossover_point, 
             sizeof(int) * (solution_size - crossover_point));
      next_offspring++;
      // offspring 2
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping, 
             parent2->m_solution.m_mapping, sizeof(int)*crossover_point);
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping+crossover_point,
             parent1->m_solution.m_mapping+crossover_point, 
             sizeof(int) * (solution_size - crossover_point));
      next_offspring++;
   }

}

void crossover_two_point(Population *population)
{
   int next_offspring = 0;
   int num_parents    = population->m_num_parents;
   int num_pairs      = num_parents/2;
   int solution_size  = population->m_parents[0]->m_solution.get_from_size();
   int p = 0;
   for (int i = 0; i < num_pairs; i++)
   {
      Individual *parent1 = population->m_selected_parents[p++];
      Individual *parent2 = population->m_selected_parents[p++];
 
      int crossover_point1 = rand() % solution_size;
      int crossover_point2 = rand() % solution_size;

      if (crossover_point2 < crossover_point1)
      {
         int temp = crossover_point1;
         crossover_point1 = crossover_point2;
         crossover_point2 = temp;
      }
   
      // offspring 1
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping, 
             parent1->m_solution.m_mapping, sizeof(int)*crossover_point1);
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping+crossover_point1,
             parent2->m_solution.m_mapping+crossover_point1, 
             sizeof(int) * (crossover_point2 - crossover_point1));
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping+crossover_point2,
             parent1->m_solution.m_mapping+crossover_point2,
             sizeof(int) * (solution_size - crossover_point2));
      next_offspring++;
      // offspring 2
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping, 
             parent2->m_solution.m_mapping, sizeof(int)*crossover_point1);
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping+crossover_point1,
             parent1->m_solution.m_mapping+crossover_point1, 
             sizeof(int) * (crossover_point2 - crossover_point1));
      memcpy(population->m_offspring[next_offspring]->m_solution.m_mapping+crossover_point2,
             parent2->m_solution.m_mapping+crossover_point2,
             sizeof(int) * (solution_size - crossover_point2));
      next_offspring++;
   }

}
}
