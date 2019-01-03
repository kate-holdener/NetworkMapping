#include <stdlib.h>
#include "Network.h"
#include "NetworkMapping.h"

int main(int argc, char **argv)
{
   double *p_weights = (double*)malloc(sizeof(double) * 3);
   double *v_weights = (double*)malloc(sizeof(double) * 3);

   double **p_matrix = (double **)malloc(sizeof(double*) * 3);
   double **v_matrix = (double **)malloc(sizeof(double*) * 3);
   for (int i = 0; i < 3; i++)
   {
      p_weights[i] = 1;
      v_weights[i] = 1;

      p_matrix[i] = (double*)calloc(3, sizeof(double));
      v_matrix[i] = (double*)calloc(3, sizeof(double));
   }

   p_matrix[0][1] = 1;
   p_matrix[1][0] = 1;
   p_matrix[1][2] = 1;
   p_matrix[2][1] = 1;

   v_matrix[0][1] = 1;
   v_matrix[1][0] = 1;
   v_matrix[1][2] = 1;
   v_matrix[2][1] = 1;
   v_matrix[0][2] = 1;
   v_matrix[2][0] = 1;
  
   Network p_network(p_matrix, p_weights, 3);
   Network v_network(v_matrix, v_weights, 3);

   printf("virtual network request:\n");
   v_network.print(stdout);
   printf("\nphysical network:\n");
   p_network.print(stdout);

   NetworkMapping vne(&v_network, &p_network);
   vne.m_mapping[0] = 0;
   vne.m_mapping[1] = 1;
   vne.m_mapping[2] = 2;

 
   printf("\nVNE\n");
   vne.print_mapping(stdout); 
   printf("Number of valid links is: %d\n", vne.valid_links());
}
