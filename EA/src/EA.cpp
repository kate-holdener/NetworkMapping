/*
 * A class representing evolutionary algorithm
 */

#include "EA.h"
#include "Initialization.h"
#include "Fitness.h"
#include "Selection.h"
#include "Crossover.h"
#include "Mutation.h"
#include "Competition.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


EA::EA(FILE *input_file_from, FILE *input_file_to):
   m_from(input_file_from),
   m_to(input_file_to),
   m_population_size(100),
   m_mutation_rate(0),
   m_mutation_percent(0),
   m_max_iter(0),
   m_current_iter(0)
{
   srand(time(NULL));
   // initialize default EA operators
   _selection = &roulette_wheel;
   _crossover = &crossover_random;
   _evaluate  = &nodes_and_links_ratio;
   _mutate    = &mutate_random;
   _compete   = &fittest_survive;
   _initialize_individual = &initialize_random;
}

EA::EA(Network *from, Network *to):
   m_from(from),
   m_to(to),
   m_population_size(100),
   m_mutation_rate(0),
   m_mutation_percent(0),
   m_max_iter(0),
   m_current_iter(0)

{
   srand(time(NULL));
   // initialize default EA operators
   _selection = &roulette_wheel;
   _crossover = &crossover_random;
   _evaluate  = &nodes_and_links_ratio;
   _mutate    = &mutate_random;
   _compete   = &fittest_survive;
   _initialize_individual = &initialize_random;
}

EA::~EA()
{
}

void EA::set_parameters(EAParameters *parameters)
{
   if (parameters->selection != NULL)
   {
      _selection = parameters->selection;
   }
   if (parameters->crossover != NULL)
   {
      _crossover = parameters->crossover;
   }
   if (parameters->evaluate != NULL)
   {
      _evaluate = parameters->evaluate;
   }
   if (parameters->mutate != NULL)
   {
      _mutate = parameters->mutate;
   }
   if (parameters->compete != NULL)
   {
      _compete = parameters->compete;
   }
   if (parameters->initialize != NULL)
   {
      _initialize_individual = parameters->initialize;
   }
   if (parameters->population_size != -1)
   {
      m_population_size = parameters->population_size;
   }
   if (parameters->mutation_rate != -1)
   {
      m_mutation_rate = parameters->mutation_rate;
   }
  
}

void EA::initialize()
{
   m_population.allocate(&m_from, &m_to, m_population_size, m_population_size);
   for (int i = 0; i < m_population_size; i++)
   {
      (*_initialize_individual)(m_population.m_parents[i]);
   }
}


void EA::mutate()
{
   for (int i = 0; i < m_population.m_num_offspring; i++)
   {
      (*_mutate)(m_population.m_offspring[i], m_mutation_rate);
   }
}

void EA::run()
{
   // Initialize the population
   initialize();

   // Evaluate the initial population
   (_evaluate)(m_population.m_parents, m_population.m_num_parents);
   printf("Best fitness at iteration %d is %f\n", m_current_iter, get_best_fitness()); 
   printf("Worst fitness at iteration %d is %f\n", m_current_iter, m_population.m_parents[m_population.m_num_parents-1]->m_fitness);

   while (1)
   {
      m_current_iter++;

      // Create offspring
      (*_selection)(&m_population);
      (*_crossover)(&m_population);

      mutate();

      // Evaluate offspring
      (*_evaluate)(m_population.m_offspring, m_population.m_num_offspring); 

      (*_compete)(&m_population);

      if ((m_current_iter & 0xFF) == 1)
      {
         m_population.sort_parents();
         printf("Best fitness at iteration %d is %f\n", m_current_iter, get_best_fitness()); 
         printf("Worst fitness at iteration %d is %f\n", m_current_iter, m_population.m_parents[m_population.m_num_parents-1]->m_fitness);
      }
      if ( terminate() )
      {
         break;
      }
   }
}
