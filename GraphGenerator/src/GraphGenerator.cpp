#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GraphGenerator.h"

void GraphGenerator::create(FILE  *out_file)
{
   if (num_nodes == 0)
   {
      fprintf(stderr, "ERROR: GraphGenerator::create - num_nodes is zero\n");
      return;
   }

   double **adjacency_matrix = new double*[num_nodes];
   for (int i = 0; i < num_nodes; i++)
   {
      adjacency_matrix[i] = new double[num_nodes];
      for (int j = 0; j < num_nodes; j++)
      {
         adjacency_matrix[i][j] = 0;
      }
   }

   double *nodes = new double[num_nodes];

   generate_node_weights(nodes);
   generate_undirected_edges(adjacency_matrix);
   generate_edge_weights(adjacency_matrix);

   print_graph(adjacency_matrix, nodes, out_file);


   //clean up memory
   for (int i = 0; i < num_nodes; i++)
   {
      delete []  adjacency_matrix[i];
   }
   delete [] adjacency_matrix;
   delete [] nodes;

}

void GraphGenerator::print_adjacency_matrix(double **adjacency_matrix, FILE *out_file)
{
   for (int i = 0; i < num_nodes; i++)
   {
      for (int j = 0; j < num_nodes; j++)
      {
         fprintf(out_file, "%f, ", adjacency_matrix[i][j]);
      }
      fprintf(out_file, "\n");
   }
}

void GraphGenerator::generate_node_weights(double *nodes)
{
   for (int i = 0; i < num_nodes; i++)
   {
      nodes[i] = min_node_weight + (rand() % (int)(max_node_weight - min_node_weight));
   }
}

void GraphGenerator::generate_edge_weights(double **adjacency_matrix)
{
   for (int i = 0; i < num_nodes; i++)
   {
      for (int j = 0; j < num_nodes; j++)
      {
         if (adjacency_matrix[i][j] != 0)
         {
            if (!directed && j < i)
            {
               adjacency_matrix[i][j] = adjacency_matrix[j][i];
            }
            else 
            {
               double weight = min_edge_weight + (rand() % (int)(max_edge_weight - min_edge_weight));
               adjacency_matrix[i][j] = weight;
            }
         }
      }
   }
}

void GraphGenerator::generate_undirected_edges(double **adjacency_matrix)
{
   int avg_degree = (int)(density * (num_nodes-1));

   for (int i = 0; i < num_nodes; i++)
   {
      // count the degree of node i
      int degree = 0;
      for (int j = 0; j < num_nodes; j++)
      {
         if (adjacency_matrix[i][j] != 0)
         {
            degree++;
         }
      }

      for (int k = 0; k < avg_degree - degree; k++)
      {
         int num_tries = 0;
         int v = rand() % num_nodes;
         // pick a vertex to connect to
         while (adjacency_matrix[i][v] != 0 || v == i)
         {
            v = (v+1) % num_nodes;
            num_tries++;
            if (num_tries == num_nodes)
            {
               break;
            }
         } 
         adjacency_matrix[i][v] = 1;
         adjacency_matrix[v][i] = 1;
      } 
   }
}

void GraphGenerator::print_graph(double **adjacency_matrix, double *nodes, FILE *out_file)
{
   for (int i = 0; i < num_nodes; i++)
   {
      int j = 0;
      if (!directed)
      {
         j = i+1;
      }
      for (j; j < num_nodes; j++)
      { 
         if (adjacency_matrix[i][j] != 0)
         {
            fprintf(out_file, "%d %d %f\n", i, j, adjacency_matrix[i][j]);
         }
      }
   }

   fprintf(out_file, "\n");
   for (int i = 0; i < num_nodes; i++)
   {
      fprintf(out_file, "%f\n", nodes[i]);
   }
}

int main(int argc, char **argv)
{
   GraphGenerator g;
   bool directed = false;
   int  num_nodes = 0;
   double density = 1;
   double min_edge_weight = 1;
   double max_edge_weight = 10;
   double min_node_weight = 1;
   double max_node_weight = 10;

   int next_arg = 1;
   while (next_arg < argc)
   {
      if (strcmp(argv[next_arg], "-nodes") == 0)
      {
         next_arg++;
         num_nodes = atoi(argv[next_arg]);
      }
      else if (strcmp(argv[next_arg], "-density") == 0)
      {
         next_arg++;
         density = atof(argv[next_arg]);
      }
      else if (strcmp(argv[next_arg], "-min_edge_weight") == 0)
      {
         next_arg++;
         min_edge_weight = atof(argv[next_arg]);
      }
      else if (strcmp(argv[next_arg], "-max_edge_weight") == 0)
      {
         next_arg++;
         max_edge_weight = atof(argv[next_arg]);
      }
      else if (strcmp(argv[next_arg], "-min_node_weight") == 0)
      {
         next_arg++;
         min_node_weight = atof(argv[next_arg]);
      }
      else if (strcmp(argv[next_arg], "-max_node_weight") == 0)
      {
         next_arg++;
         max_node_weight = atof(argv[next_arg]);
      }
      next_arg++;
   }
   // initialize random number generator
   srand(time(NULL));

   g.set_num_nodes(num_nodes);
   g.set_directed(directed);
   g.set_density(density);
   g.set_min_edge_weight(min_edge_weight);
   g.set_max_edge_weight(max_edge_weight);
   g.set_min_node_weight(min_node_weight);
   g.set_max_node_weight(max_node_weight);
   g.create(stdout);
}
