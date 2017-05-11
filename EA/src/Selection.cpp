#include "Selection.h"

inline bool compare_score(Individual *s1, Individual *s2)
{
   return (s1->m_score > s2->m_score) ? true : false;
}
void select_by_score(Population *population)
{
   double probability = 0;
   double total_score = 0;
   for (int i = 0; i < population->m_num_selected_parents; i++)
   {
      probability = (rand() % 100)/100.0;
      for (int j = 0; j < population->m_num_parents; j++)
      {
         total_score += population->m_parents[j]->m_score;
         if (probability < total_score)
         {
            population->m_selected_parents[i] = population->m_parents[j];
            break;
         }
      }
   }
}

extern "C"
{
void roulette_wheel(Population *population)
{
   double sum_fitness = 0;
   for (int i = 0; i < population->m_num_parents; i++)
   {
      sum_fitness += population->m_parents[i]->m_fitness;
   }

   for (int i = 0; i < population->m_num_parents; i++)
   {
      population->m_parents[i]->m_score = population->m_parents[i]->m_fitness/sum_fitness;
   }
   //sort the parents based on score
   std::sort(population->m_parents, population->m_parents + population->m_num_parents, compare_score); 
   select_by_score(population);
}

void rank(Population *population)
{
   double sum_fitness = population->m_num_parents * (population->m_num_parents+1) / 2;
   population->sort_parents();
   
   for (int i = 0; i < population->m_num_parents; i++)
   {
      population->m_parents[i]->m_score = (population->m_num_parents - i ) / sum_fitness; 
   }
   select_by_score(population);
}
}
