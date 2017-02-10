/* 
 * A class representing a mapping from a virtual network to a physical network
 */

#ifndef NETWORK_MAPPING_H
#define NETWORK_MAPPING_H

#include "Network.h"

struct Link
{
   Link(int r, int c, int w):row(r),column(c),weight(w){}
   int row;
   int column;
   int weight;
};


class NetworkMapping
{
public:
   NetworkMapping(Network *from, Network *to);

   virtual ~NetworkMapping();

   /*
    * Calculates and returns the number of nodes whose weight constraints
    * are satisfied under this mapping
    */ 
   int valid_nodes();

   /*
    * Calculates and returns the ratio of number of nodes whose weight 
    * constraints are satisfied under this mapping to the total number
    * of nodes
    */
   inline double valid_nodes_ratio() { return ((double)valid_nodes())/m_from->size(); }

   /*
    * Calculates and returns the number of links whose weight constraints
    * are satisfied under this mapping
    */
   int valid_links();

   /*
    * Calculates and returns the ratio of the number of links whose weight
    * constraints are satisfied under this mapping to the total number of links
    */
   inline double valid_links_ratio() { return ((double)valid_links())/m_num_links; }

   void print_mapping(FILE *output_file);
 
   int     *m_mapping;       // an array of size m_from->size()
private:

   void reset_node_capacity();
   void reset_link_capacity();

   Network *m_from;
   Network *m_to;

   Network  m_link_capacity; // a copy of m_to, modified to reflect the risidual
                             // capacity of m_to under this mapping
   int     *m_node_capacity; // an array of size m_to->size()


   Link    *m_sorted_links;  // link indices of the m_from network, sorted in descending order
   int      m_num_links;     // size of m_sorted_links array
};
#endif

