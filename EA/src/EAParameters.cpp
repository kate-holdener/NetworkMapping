#include "EAParameters.h"
#include "Initialization.h"
#include "Mutation.h"
#include "Fitness.h"
#include "Competition.h"
#include "Crossover.h"

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <dlfcn.h>

const std::string c_initialize = "initialize";
const std::string c_selection = "selection";
const std::string c_crossover = "crossover";
const std::string c_mutation = "mutation";
const std::string c_compete = "compete";
const std::string c_fitness = "fitness";
const std::string c_population_size = "population_size";
const std::string c_mutation_rate = "mutation_rate";

void trim(std::string &str)
{
   str.erase(0, str.find_first_not_of(' '));
   str.erase(str.find_last_not_of(' ') + 1);
   str.erase(str.find_last_not_of('\n') +1);
}
 
EAParameters::EAParameters():
   selection(NULL),
   crossover(NULL),
   evaluate(NULL),
   mutate(NULL),
   compete(NULL),
   initialize(NULL),
   population_size(-1),
   mutation_rate(-1)
{}

void EAParameters::read_from_file(const char *file_name)
{
   FILE *input_file = fopen(file_name, "r");
   const int line_size = 1024;
   char line[line_size];
   std::string line_string;
   std::string param_name;
   std::string param_value;

   size_t  pos = std::string::npos;

   void* handle = dlopen(NULL, RTLD_LAZY|RTLD_GLOBAL);
   if (handle == NULL)
   {
       fprintf(stderr, "ERROR: EAParameteres:read_from_file(): dlopen() failed\n");
       return;
   }
   if (input_file == NULL)
   {
      fprintf(stderr, "ERROR: EAParameters:read_from_file() failed to open %s\n", 
         file_name);
      return;
   }
   while (fgets(line, line_size, input_file) != NULL)
   {
      line_string = line;
      pos = line_string.find(':');
      if (pos != std::string::npos)
      {
         param_name = line_string.substr(0, pos);
         param_value = line_string.substr(pos+1);
         trim(param_name);
         trim(param_value);
         if (param_name == c_selection)
         {
            selection = (selection_f)dlsym(handle, param_value.c_str());
            if (selection == NULL)
            {
               fprintf(stderr, "ERROR: EAParameters:read_from_file() failed on dlsym(%s): %s\n", param_value.c_str(), dlerror());
            }

         }
         else if (param_name == c_crossover)
         {
            crossover = (crossover_f)dlsym(handle, param_value.c_str());
            if (crossover == NULL)
            {
               fprintf(stderr, "ERROR: EAParameters:read_from_file() failed on dlsym(%s): %s\n", param_value.c_str(), dlerror());
            }
         }
         else if (param_name == c_fitness)
         {
            evaluate = (evaluate_f)dlsym(handle, param_value.c_str());
            if (initialize == NULL)
            {
               fprintf(stderr, "ERROR: EAParameters:read_from_file() failed on dlsym(%s)\n", param_value.c_str());
            }
         }
         else if (param_name == c_mutation)
         {
            mutate = (mutate_f)dlsym(handle, param_value.c_str());
            if (mutate == NULL)
            {
               fprintf(stderr, "ERROR: EAParameters:read_from_file() failed on dlsym(%s)\n", param_value.c_str());
            }
         }
         else if (param_name == c_compete)
         {
            compete = (compete_f)dlsym(handle, param_value.c_str());
            if (compete == NULL)
            {
               fprintf(stderr, "ERROR: EAParameters:read_from_file() failed on dlsym(%s)\n", param_value.c_str());
            }
         }
         else if (param_name == c_initialize)
         {
            initialize = (initialize_individual_f)dlsym(handle, param_value.c_str());
            if (initialize == NULL)
            {
               fprintf(stderr, "ERROR: EAParameters:read_from_file() failed on dlsym(%s)\n", param_value.c_str());
            }
         }
         else if (param_name == c_population_size)
         {
            population_size = atoi(param_value.c_str());
         }
         else if (param_name == c_mutation_rate)
         {
            mutation_rate = atof(param_value.c_str());
         }
      }
   }
   dlclose(handle);
      
}
