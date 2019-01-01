/*
 * EA individual, representing a potential solution to the Network Mapping
 * problem, along with its fitness value
 */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "NetworkMapping.h"

class Individual
{
public:
   /*
    * Constructor
    * @param from [IN] virtual network
    * @param to   [IN] physical network
    */
   Individual(Network *from, Network *to):
      m_solution(from, to),
      m_feasible(0),
      m_fitness(0),
      m_score(0)
   {}

   virtual ~Individual(){}

   void* operator new (size_t size, Individual *individual)
   {
      return individual;
   }

   NetworkMapping m_solution;

   bool           m_feasible;
   double         m_fitness;
   double         m_score; // used in selection
};

#endif
