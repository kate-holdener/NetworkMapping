/*
 * Network class impelents graph as a collection of weighted nodes and
 * weighted edges
 */

#include "Network.h"
#include "parse.h"
#include <queue>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Network::Network(FILE *input_file):
  m_link_weights(NULL),
  m_node_weights(NULL),
  m_size(0)
{
   // File format is:
   // list of links (one link per line in the format: node1 node2 link_weight)
   // list of node weights (one node per line)
   size_t line_size = 1024;
   char  *line = (char*) alloca(line_size);
   int    num_values = 0;
   int    values[3];
   int    node = 0;

   // initialize m_size
   init_size(input_file);

   // allocate m_link_weights and m_node_weights based on the number of nodes 
   m_link_weights = (int**)malloc(sizeof(int*) * m_size);
   for (int i = 0; i < m_size; i++)
   {
      m_link_weights[i] = (int*)malloc(sizeof(int) * m_size);
      for (int j = 0; j < m_size; j++)
      {
         m_link_weights[i][j] = -1;
      }
   }

   m_node_weights = (int*)malloc(sizeof(int) * m_size);
   memset(m_node_weights, 0, sizeof(int) * m_size);

   // rewind to the start of input_file
   rewind(input_file);

   // read one line at a time to fill in m_link_weights
   
   while ( fgets(line, line_size, input_file) != NULL)
   {
      num_values = 3;
      parse_line(line, values, &num_values);
      // if no weight was specified, set it to 1
      if (num_values == 2)
      {
         values[2] = 0;
         num_values = 3;
      }
      if (num_values == 3)
      {
         m_link_weights[values[0]][values[1]] = values[2];
         m_link_weights[values[1]][values[0]] = values[2];
      }
      // if we are here, we are now processing node weights, not edges
      else if (num_values == 1)
      {
         m_node_weights[node] = values[0];
         node++;
      }
      line_size = 1024;
   }  

}

void Network::init_size(FILE *input_file)
{
   size_t line_size = 1024;
   char  *line = (char*) alloca(line_size);
   int    num_values = 0;
   int    values[2];

   // first pass through the file to determine the number of nodes
   while ( fgets(line, line_size, input_file) != NULL)
   {
      num_values = 2;
      parse_line(line, values, &num_values);
      if (num_values == 2)
      {
         if (values[0] >= m_size)
         {
            m_size = values[0] + 1;
         }
         if (values[1] >= m_size)
         {
            m_size = values[1] + 1;
         }
      }
      // if we are here, we are now processing node weights, not edges
      else if (num_values == 1)
      {
         break;
      }
   }  
}

Network::Network(Network *network):
   m_link_weights(NULL),
   m_node_weights(NULL),
   m_size(network->m_size)
{
   // allocate and copy adjacency matrix
   m_link_weights = (int**)malloc(sizeof(int*) * m_size);
   for (int i = 0; i < m_size; i++)
   {
      m_link_weights[i] = (int*)malloc(sizeof(int) * m_size);
      memcpy(m_link_weights[i], network->m_link_weights[i], sizeof(int) * m_size);
   }

   // allocate and copy node weighs
   m_node_weights = (int*)malloc(sizeof(int) * m_size);
   memcpy(m_node_weights, network->m_node_weights, sizeof(int) * m_size);
  
}

Network& Network::operator=(Network *network)
{
   assert(m_size == network->m_size);
   for (int i = 0; i < m_size; i++)
   {
      memcpy(m_link_weights[i], network->m_link_weights[i], sizeof(int) * m_size);
   };
   
   memcpy(m_node_weights, network->m_node_weights, sizeof(int) * m_size);
}

Network::Network(int **matrix, int *weights, int size):
   m_link_weights(NULL),
   m_node_weights(NULL),
   m_size(size)
{
   // allocate and copy adjacency matrix
   m_link_weights = (int**)malloc(sizeof(int*) * m_size);
   for (int i = 0; i < m_size; i++)
   {
      m_link_weights[i] = (int*)malloc(sizeof(int) * m_size);
      memcpy(m_link_weights[i], matrix[i], sizeof(int) * m_size);
   }

   // allocate and copy node weighs
   m_node_weights = (int*)malloc(sizeof(int) * m_size);
   memcpy(m_node_weights, weights, sizeof(int) * m_size);
}

Network::~Network()
{
   for (int i = 0; i < m_size; i++)
   {
      free(m_link_weights[i]);
   }
   free(m_link_weights);
   m_link_weights = NULL;
   free(m_node_weights);
   m_node_weights = NULL;
   m_size = 0;
}

bool Network::path_exists(int node1, int node2, int weight)
{
   std::queue<int> node_list;
   bool *node_selected = (bool*) alloca(sizeof(bool) * m_size);
   memset(node_selected, 0, sizeof(bool) * m_size);
   node_selected[node1] = true;

#ifdef MY_DEBUG
   printf("Processing adjacency list for node %d\n", node1);
#endif

   for (int i = 0; i < m_size; i++)
   {
      if(m_link_weights[node1][i] >= weight)
      {
         // found the path
         if (i == node2)
         {
            return true;
         }
         node_list.push(i);
         node_selected[i] = true;
#ifdef MY_DEBUG
         printf("Added node %d \n", i);
#endif
      }
   }  

   while (!node_list.empty())
   {
      int node = node_list.front();
#ifdef MY_DEBUG
      printf("Processing adjacency list for node %d\n", node);
#endif

      for (int i = 0; i < m_size; i++)
      {
         if (m_link_weights[node][i] >= weight && !node_selected[i])
         {
            // found the path
            if (i == node2)
            {
               return true;
            }
            node_list.push(i);
            node_selected[i] = true;
#ifdef MY_DEBUG
            printf("Added node %d \n", i);
#endif
         }
      }
      node_list.pop();
   }

   // if we are here, we did not find the path
   return false;
}

bool Network::embed_path(int node1, int node2, int weight)
{
   if (node1 == node2)
   {
      return true;
   }
   std::queue<int> node_list;
   int *node_ancestor = (int*) alloca(sizeof(int) * m_size);
   for (int i = 0; i < m_size; i++)
   {
      node_ancestor[i] = -1;
   }
   node_ancestor[node1] = node1;
#ifdef MY_DEBUG
   printf("Processing adjacency list for node %d\n", node1);
#endif

   for (int i = 0; i < m_size; i++)
   {
      if(m_link_weights[node1][i] >= weight)
      {
         node_ancestor[i] = node1;
         // found the path
         if (i == node2)
         {
            reduce_capacity(node1, node2, node_ancestor, weight);   
            return true;
         }
         node_list.push(i);
#ifdef MY_DEBUG
         printf("Added node %d \n", i);
#endif
      }
   }  

   while (!node_list.empty())
   {
      int node = node_list.front();
#ifdef MY_DEBUG
      printf("Processing adjacency list for node %d\n", node);
#endif

      for (int i = 0; i < m_size; i++)
      {
         if (m_link_weights[node][i] >= weight && node_ancestor[i] < 0)
         {
            node_ancestor[i] = node;
            // found the path
            if (i == node2)
            {
#ifdef MY_DEBUG
               for (int a = 0; a < m_size; a++)
               {
                  printf("%d, ", node_ancestor[a]);
               }
               printf("\n");
#endif
               reduce_capacity(node1, node2, node_ancestor, weight);
               return true;
            }
            node_list.push(i);
#ifdef MY_DEBUG
            printf("Added node %d \n", i);
#endif
         }
      }
      node_list.pop();
   }

   // if we are here, we did not find the path
   return false;

}

void Network::reduce_capacity(int node1, int node2, int *node_ancestor, int weight)
{
   int current_node = node2;
   int previous_node = node2;
   while (current_node != node1)
   {
      previous_node = node_ancestor[current_node];
      m_link_weights[current_node][previous_node]-= weight;
      m_link_weights[previous_node][current_node]-= weight;
      current_node = previous_node;
   }
}

