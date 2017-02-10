#include "EA.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
   char *network_virtual = NULL;
   char *network_physical = NULL;
   FILE *network_virtual_f = NULL;
   FILE *network_physical_f = NULL;

   int   num_errors = 0;

   for (int a = 0; a < argc; a++)
   {
      if (strcmp(argv[a], "-virtual") == 0 && (a +1 < argc))
      {
         a++;
         network_virtual = argv[a];
      }
      else if (strcmp(argv[a], "-physical") == 0 && (a +1 < argc))
      {
         a++;
         network_physical = argv[a];
      }
   }


   if (network_virtual == NULL || network_physical == NULL)
   {
      printf("USAGE: ./Solver -virtual <VIRTUAL_NETWORK_FILE> -physical <PHYSICAL_NETWORK_FILE>\n");
      return 0;
   }

   printf("Using: \n %s - virtual network \n %s - physical network\n",
      network_virtual, network_physical);

   network_virtual_f = fopen(network_virtual, "r");
   network_physical_f = fopen(network_physical, "r");
   if (network_virtual_f == NULL)
   {
      fprintf(stderr, "ERROR: could not open virtual network file %s\n", network_virtual);
      num_errors++;
   }
   if (network_physical_f == NULL)
   {
      fprintf(stderr, "ERROR: could not open physical network file %s\n", network_physical);
      num_errors++;
   }

   if (num_errors == 0)
   {
      EA ea(network_virtual_f, network_physical_f);
      ea.set_population_size(100);
      ea.set_mutation_rate(0.1);
      ea.set_max_iter(100);
      ea.run();
      printf("Best solution has fitness %f\n", ea.get_best_fitness());
      NetworkMapping *best_solution = ea.get_best_solution();
      best_solution->print_mapping(stdout);
      printf("Valid nodes ratio %f\n", best_solution->valid_nodes_ratio());
      printf("Valid links ratio %f\n", best_solution->valid_links_ratio());
   }
  
   fclose(network_virtual_f);
   fclose(network_physical_f);

   return 0;
}
