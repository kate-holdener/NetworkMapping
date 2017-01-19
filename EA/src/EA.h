/*
 * A class representing evolutionary algorithm
 */

#ifndef EA_H
#define EA_H

#include "Individual.h"
#include <stdio.h>

class EA
{
public:
   /*
    *  Constructor used to intialize EA with an input file
    */
   EA(FILE *input_file_from, FILE *input_file_to);

   /*
    * Constructor used to initialize EA with virtual and physical networs
    */
   EA(Network *from, Network *to);

   ~EA();

   void set_population_size(int population_size){m_population_size = population_size;}

   void set_mutation_rate(float mutation_rate)
   {
      m_mutation_rate = mutation_rate; 
      m_mutation_percent = m_mutation_rate * 100;
   }

   void run();   
private:
 
   /*
    * Allocate and initialize the population at random
    */
   void initialize();

   /*
    * Evaluates the fitness of the given array of individuals 
    */ 
   void evaluate(Individual **individuals, int num_individuals);

   /*
    * Performs crossover on m_population to generate m_offspring
    */
   void crossover();

   /*
    * Perform mutation on the offspring
    */ 
   void mutate();

   /*
    * Perform competition among m_population and m_offspring
    */
   void compete();

   Network m_from;   // virtual network
   Network m_to;     // physical network

   // EA parameters
   int   m_population_size;
   float m_mutation_rate;
   int   m_mutation_percent;

   Individual **m_population;
   Individual **m_offspring;

   Individual *m_pool;
   int         m_pool_size;
};
#endif

