/*
 * A class representing evolutionary algorithm
 */

#include "EA.h"
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <time.h>

bool compare_fitness(Individual *s1, Individual *s2)
{
   return (s1->m_fitness > s2->m_fitness) ? true : false;
}


EA::EA(FILE *input_file_from, FILE *input_file_to):
   m_from(input_file_from),
   m_to(input_file_to),
   m_population_size(100),
   m_mutation_rate(0),
   m_mutation_percent(0),
   m_max_iter(0),
   m_current_iter(0),
   m_population(NULL),
   m_offspring(NULL),
   m_pool(NULL),
   m_pool_size(0)
{
   srand(time(NULL));
}

EA::EA(Network *from, Network *to):
   m_from(from),
   m_to(to),
   m_population_size(100),
   m_mutation_rate(0),
   m_population(NULL),
   m_offspring(NULL),
   m_pool(NULL),
   m_pool_size(0)
{}

EA::~EA()
{
   free(m_offspring);
   m_population_size = 0;
   m_offspring = NULL;
   free(m_population);
   m_population = NULL;
   for (int i = 0; i < m_pool_size; i++)
   {
      m_pool[i].~Individual();
   }
   free(m_pool);
   m_pool_size = 0;
   m_pool = NULL;
}

void EA::initialize()
{
   // pool size is twice the population size: half is used for the
   // current population, the other half is used for offspring
   m_pool_size = m_population_size * 2;
   m_pool = (Individual*)malloc(sizeof(Individual) * m_pool_size);
   for (int i = 0; i < m_pool_size; i++)
   {
      new (m_pool + i)Individual(&m_from, &m_to);
   }

   // allocate space to store population and offspring
   // randomly initialize population
   m_population = (Individual**)malloc(sizeof(Individual*) * m_population_size);
   m_offspring = (Individual**)malloc(sizeof(Individual*) * m_population_size);
   for (int i = 0; i < m_population_size; i++)
   {
      m_population[i] = &m_pool[i];
      m_offspring[i] = &m_pool[i+m_population_size];
      for (int j = 0; j < m_from.size(); j++)
      {
         m_population[i]->m_solution.m_mapping[j] = rand() % m_to.size();
      }
   }
   evaluate(m_population, m_population_size);
   std::sort(m_population, m_population+m_population_size, compare_fitness);
}


void EA::evaluate(Individual **individuals, int num_individuals)
{
   for (int i = 0; i < num_individuals; i++)
   {
      individuals[i]->m_fitness =  
         individuals[i]->m_solution.valid_nodes_ratio() + 
         individuals[i]->m_solution.valid_links_ratio();
   }
}

void EA::crossover()
{
   int next_offspring = 0;
   int num_pairs = m_population_size/2;

   for (int i = 0; i < num_pairs; i++)
   {
      int index1 = rand() % m_population_size;
      int index2 = rand() % m_population_size;
      if (index1 == index2)
      {
         index2 = (index2+1) % m_population_size;
      }
      Individual *parent1 = m_population[index1];
      Individual *parent2 = m_population[index2];
 
      int crossover_point = rand() & m_from.size();
      if (crossover_point == 0)
      {
         crossover_point = 1;
      }
    
      // offspring 1
      memcpy(m_offspring[next_offspring]->m_solution.m_mapping, 
             parent1->m_solution.m_mapping, sizeof(int)*crossover_point);
      memcpy(m_offspring[next_offspring]->m_solution.m_mapping+crossover_point,
             parent2->m_solution.m_mapping+crossover_point, 
             sizeof(int) * (m_from.size() - crossover_point));
      next_offspring++;
      // offspring 2
      memcpy(m_offspring[next_offspring]->m_solution.m_mapping, 
             parent2->m_solution.m_mapping, sizeof(int)*crossover_point);
      memcpy(m_offspring[next_offspring]->m_solution.m_mapping+crossover_point,
             parent1->m_solution.m_mapping+crossover_point, 
             sizeof(int) * (m_from.size() - crossover_point));
      next_offspring++;
   }
}

void EA::mutate()
{
   int mutation_point;
   for (int i = 0; i < m_population_size; i++)
   {
      if (rand() % 100 < m_mutation_percent)
      {
         // pick mutation point
         mutation_point = rand() % m_from.size();
         m_offspring[i]->m_solution.m_mapping[mutation_point] = rand() % m_to.size();
      }
   }
}

void EA::compete()
{
   std::sort(m_offspring, m_offspring+m_population_size, compare_fitness);
   std::sort(m_population, m_population+m_population_size, compare_fitness);

   int i;
   for (i = m_population_size-1; i >=0; i--)
   {
      if ( compare_fitness(m_population[i], m_offspring[0]) )
      {
         break;
      }
   }   
 
   int offspring_index = 0;

   for (i = i+1; i < m_population_size; i++)
   {
      if (compare_fitness(m_offspring[offspring_index], m_population[i]) )
      {
         Individual *temp = m_population[i];
         m_population[i] = m_offspring[offspring_index];
         m_offspring[offspring_index] = temp;
         offspring_index++;
      }
   }
}

void EA::run()
{
   // Initialize the population
   initialize(); 

   // Evaluate the initial population
   evaluate(m_population, m_population_size);

   while (1)
   {
      m_current_iter++;

      // Create offspring
      crossover();
      mutate();

      // Evaluate offspring
      evaluate(m_offspring, m_population_size); 

      compete();
      if ( terminate() )
      {
         break;
      }
   }
}
