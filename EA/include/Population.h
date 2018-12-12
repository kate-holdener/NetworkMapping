/*
 * A class representing EA's population
 * (collection of candidate solutions)
 */

#ifndef POPULATION_H
#define POPULATION_H

#include "Individual.h"
#include <algorithm>

inline bool compare_fitness(Individual *s1, Individual *s2)
{
   return (s1->m_fitness > s2->m_fitness) ? true : false;
}


class Population
{
public:
   Population():
      m_parents(NULL),
      m_selected_parents(NULL),
      m_offspring(NULL),
      m_pool(NULL),
      m_num_parents(0),
      m_num_selected_parents(0),
      m_num_offspring(0),
      m_pool_size(0)
   {}

   virtual ~Population();

   inline void sort()
   {
      std::sort(m_parents, m_parents + m_num_parents, compare_fitness);
      std::sort(m_offspring, m_offspring + m_num_offspring, compare_fitness);
   }

   inline void sort_parents()
   {
      std::sort(m_parents, m_parents + m_num_parents, compare_fitness);
   }
   /*
    * Allocates space to store num_parents and num_offspring individuals, defined
    * as a mapping from the 'from' network to the 'to' network.
    */
   void allocate(Network *from, Network *to, int num_parents, int num_offspring);

   inline Individual* get_best_solution()
   {
      std::sort(m_parents, m_parents + m_num_parents, compare_fitness);
      return m_parents[0];
   }
   Individual **m_parents;
   Individual **m_selected_parents;
   Individual **m_offspring;
   Individual  *m_pool;
   int          m_num_parents;
   int          m_num_selected_parents;
   int          m_num_offspring;
   int          m_pool_size;

};

#endif
