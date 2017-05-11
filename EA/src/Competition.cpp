/*
 * Various competition functions that could be plugged into the EA 
 */

#include "Competition.h"
#include <algorithm>

extern "C"
{

void fittest_survive(Population *population)
{
   population->sort();

   int i;
   for (i = population->m_num_parents-1; i >=0; i--)
   {
      if ( compare_fitness(population->m_parents[i], population->m_offspring[0]) )
      {
         break;
      }
   }   
 
   int offspring_index = 0;

   for (i = i+1; i < population->m_num_parents; i++)
   {
      if (compare_fitness(population->m_offspring[offspring_index], population->m_parents[i]) )
      {
         Individual *temp = population->m_parents[i];
         population->m_parents[i] = population->m_offspring[offspring_index];
         population->m_offspring[offspring_index] = temp;
         offspring_index++;
      }
   }
}

void replace(Population *population)
{
   int start = population->m_num_parents - population->m_num_offspring;
   if (start < 0)
   {
      start = 0; 
   }
   for (int i = start; i < population->m_num_parents; i++)
   {
      if (i >= population->m_num_offspring)
      {
         break;
      }
      population->m_parents[i] = population->m_offspring[i];
   }
}

void replace_half(Population *population)
{
   population->sort();
   int j = 0;
   for (int i = population->m_num_parents/2; i < population->m_num_parents; i++)
   {
      population->m_parents[i] = population->m_offspring[j];
      j++;
   }
}
}
