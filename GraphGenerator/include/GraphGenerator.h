/*
 *
 */

#ifndef GRAPH_GENERATOR
#define GRAPH_GENERATOR

#include <stdio.h>
class GraphGenerator
{
public:

   GraphGenerator():
      num_nodes(0),
      directed(false),
      density(0),
      min_edge_weight(0),
      max_edge_weight(0),
      min_node_weight(0),
      max_node_weight(0)
   {}

   void create(FILE  *out_file);

   void set_num_nodes(int n)
   {
      num_nodes = n;
   }

   void set_directed(bool d)
   {
      directed = d;
   }

   void set_density(double d)
   {
      density = d;
   }
 
   void set_min_edge_weight(double w)
   {
      min_edge_weight = w;
   }

   void set_max_edge_weight(double w)
   {
      max_edge_weight = w;
   }

   void set_min_node_weight(double w)
   {
      min_node_weight = w;
   }

   void set_max_node_weight(double w)
   {
      max_node_weight = w;
   }

private:
   int    num_nodes;
   bool   directed;
   double density;
   double min_edge_weight;
   double max_edge_weight;
   double min_node_weight;
   double max_node_weight;


   void print_adjacency_matrix(double **adjacency_matrix, FILE *out_file);

   void generate_node_weights(double *nodes);
   
   void generate_edge_weights(double **adjacency_matrix);

   void generate_undirected_edges(double **adjacency_matrix);
 
   void print_graph(double **adjacency_matrix, double *nodes, FILE *out_file);
};
#endif
