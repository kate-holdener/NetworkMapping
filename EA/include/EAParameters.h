#ifndef EA_PARAMETERS_H
#define EA_PARAMETERS_H

#include "Population.h"
#include "Individual.h"

typedef void (*selection_f)(Population *population);
typedef void (*crossover_f)(Population *population);
typedef void (*evaluate_f)(Individual **individuals, int num_individuals);
typedef void (*mutate_f)(Individual *individual, float mutation_rate);
typedef void (*compete_f)(Population *population);
typedef void (*initialize_individual_f)(Individual *individual);

class EAParameters
{

public:
   EAParameters();

   void read_from_file(const char *file_name);

   selection_f selection;
   crossover_f crossover;
   evaluate_f  evaluate;
   mutate_f    mutate;
   compete_f   compete;
   initialize_individual_f initialize;

   int population_size;
   float mutation_rate;

};

#endif
