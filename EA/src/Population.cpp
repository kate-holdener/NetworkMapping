/*
 * A class representing EA's population
 * (collection of candidate solutions)
 */


#include "Population.h"
#include <stdlib.h>

Population::~Population()
{
   free(m_offspring);
   m_num_offspring = 0;
   m_offspring     = NULL;

   free(m_selected_parents);
   m_num_selected_parents = 0;
   m_selected_parents = NULL;

   free(m_parents);
   m_num_parents = 0;
   m_parents     = NULL;

   for (int i = 0; i < m_pool_size; i++)
   {
      m_pool[i].~Individual();
   }
   free(m_pool);
   m_pool_size = 0;
   m_pool      = NULL;
}

void Population::allocate(Network *from, 
                          Network *to, 
                          int      num_parents, 
                          int      num_offspring)
{
   m_num_parents = num_parents;
   m_num_offspring = num_offspring;
   m_num_selected_parents = num_offspring;

   // pool size is the sum of num_parents and num_offspring
   int pool_size = num_parents + num_offspring;
   if (m_pool_size < pool_size)
   {
      m_pool = (Individual*)realloc(m_pool, sizeof(Individual) * pool_size);
      for (int i = m_pool_size; i < pool_size; i++)
      {
         new (m_pool + i)Individual(from, to);
      }
   }
   m_pool_size = pool_size;

   // allocate space to store parents and offspring
   m_parents = (Individual**)realloc(m_parents, sizeof(Individual*) * m_num_parents);
   m_offspring = (Individual**)realloc(m_offspring, sizeof(Individual*) * m_num_offspring);
   m_selected_parents = (Individual**)realloc(m_selected_parents, sizeof(Individual*) * m_num_selected_parents);
   for (int i = 0; i < m_num_parents; i++)
   {
      m_parents[i] = &m_pool[i];
      m_offspring[i] = &m_pool[i+m_num_parents];
   }

}

