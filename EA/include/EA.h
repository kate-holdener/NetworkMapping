/*
 * A class representing evolutionary algorithm
 */

#ifndef EA_H
#define EA_H

#include "EAParameters.h"
#include "Individual.h"
#include "Population.h"
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

   void set_parameters(EAParameters *parameters);

   inline void set_population_size(int population_size){m_population_size = population_size;}

   inline void set_mutation_rate(float mutation_rate)
   {
      m_mutation_rate = mutation_rate; 
      m_mutation_percent = m_mutation_rate * 100;
   }

   inline void set_max_iter(int max_iter){m_max_iter = max_iter;}

   inline Individual* get_best_solution(){return m_population.get_best_solution();}

   inline double get_best_fitness(){return (get_best_solution())->m_fitness;}

   void run();   
private:
 
   // function pointers to EA operators 
/*
   void (*_crossover)(Population *population);
   void (*_evaluate)(Individual **individuals, int num_individuals);
   void (*_mutate)(Individual *individual);
   void (*_compete)(Population *population);
   void (*_initialize_individual)(Individual *individual);
*/
   selection_f _selection;
   crossover_f _crossover;
   evaluate_f  _evaluate;
   mutate_f    _mutate;
   compete_f   _compete;
   initialize_individual_f _initialize_individual;

   /*
    * Initializes the population
    */
   void initialize();

   /*
    * Perform mutation on the offspring
    */ 
   void mutate();

   /*
    * Termination check
    */
   inline bool terminate()
   {
/*
      if (m_current_iter < m_max_iter)
      {
         return false;
      }
*/
      if (get_best_fitness() < 1)
      {
         return false;
      }
      
      printf("Terminating after %d iterations\n", m_current_iter);
      return true;
   }


   Network m_from;   // virtual network
   Network m_to;     // physical network

   // EA parameters
   int   m_population_size;
   float m_mutation_rate;
   int   m_mutation_percent;
   int   m_max_iter;

   // Parameters describing the state of the EA
   int   m_current_iter;

   Population m_population;
};
#endif

