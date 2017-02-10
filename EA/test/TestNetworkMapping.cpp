#define private public
#include "Network.h"
#include "NetworkMapping.h"
#include <gtest/gtest.h>

TEST(LineNetwork, ValidNodes)
{
   int from_edges[2][2] = 
   {
      {0, 1},
      {1, 0}
   };
   int from_weights[2] = {1, 1};
   int *from_matrix[2];
   for (int i = 0; i < 2; i++)
   {
      from_matrix[i] = from_edges[i];
   }
 
   Network from_network((int**)from_matrix, from_weights, 2);


   int to_edges[5][5] =
   { 
     {0, 2, 0, 0, 0},
     {2, 0, 2, 0, 0},
     {0, 2, 0, 2, 0},
     {0, 0, 2, 0, 2},
     {0, 0, 0, 2, 0}
   };

   int to_weights[5] = {1, 1, 1, 1, 1};
   int *to_matrix[5];
   for (int i = 0; i < 5; i++)
   {
      to_matrix[i] = to_edges[i];
   }
 
   Network to_network((int**)to_matrix, to_weights, 5);
   
   NetworkMapping mapping(&from_network, &to_network);
   mapping.m_mapping[0] = 0;
   mapping.m_mapping[1] = 4;
   int valid_nodes = mapping.valid_nodes();
   ASSERT_EQ(2, valid_nodes);
}

TEST(LineNetwork, ValidNodesRepeated)
{
   int from_edges[2][2] = 
   {
      {0, 1},
      {1, 0}
   };
   int from_weights[2] = {1, 1};
   int *from_matrix[2];
   for (int i = 0; i < 2; i++)
   {
      from_matrix[i] = from_edges[i];
   }
 
   Network from_network((int**)from_matrix, from_weights, 2);


   int to_edges[5][5] =
   { 
     {0, 2, 0, 0, 0},
     {2, 0, 2, 0, 0},
     {0, 2, 0, 2, 0},
     {0, 0, 2, 0, 2},
     {0, 0, 0, 2, 0}
   };

   int to_weights[5] = {1, 1, 1, 1, 1};
   int *to_matrix[5];
   for (int i = 0; i < 5; i++)
   {
      to_matrix[i] = to_edges[i];
   }
 
   Network to_network((int**)to_matrix, to_weights, 5);
   
   NetworkMapping mapping(&from_network, &to_network);
   mapping.m_mapping[0] = 0;
   mapping.m_mapping[1] = 4;
   int valid_nodes = mapping.valid_nodes();
   ASSERT_EQ(2, valid_nodes);
   valid_nodes = mapping.valid_nodes();
   ASSERT_EQ(2, valid_nodes);
}


TEST(LineNetwork, ValidLinks)
{
   int from_edges[2][2] = 
   {
      {0, 1},
      {1, 0}
   };
   int from_weights[2] = {1, 1};
   int *from_matrix[2];
   for (int i = 0; i < 2; i++)
   {
      from_matrix[i] = from_edges[i];
   }
 
   Network from_network((int**)from_matrix, from_weights, 2);


   int to_edges[5][5] =
   { 
     {0, 2, 0, 0, 0},
     {2, 0, 2, 0, 0},
     {0, 2, 0, 2, 0},
     {0, 0, 2, 0, 2},
     {0, 0, 0, 2, 0}
   };

   int to_weights[5] = {1, 1, 1, 1, 1};
   int *to_matrix[5];
   for (int i = 0; i < 5; i++)
   {
      to_matrix[i] = to_edges[i];
   }
 
   Network to_network((int**)to_matrix, to_weights, 5);
   
   NetworkMapping mapping(&from_network, &to_network);
   mapping.m_mapping[0] = 0;
   mapping.m_mapping[1] = 4;
   int valid_links = mapping.valid_links();
   ASSERT_EQ(1, valid_links);
}

TEST(LineNetwork, ValidLinksRepeated)
{
   int from_edges[2][2] = 
   {
      {0, 1},
      {1, 0}
   };
   int from_weights[2] = {1, 1};
   int *from_matrix[2];
   for (int i = 0; i < 2; i++)
   {
      from_matrix[i] = from_edges[i];
   }
 
   Network from_network((int**)from_matrix, from_weights, 2);


   int to_edges[5][5] =
   { 
     {0, 2, -1, -1, -1},
     {2, 0, 2, -1, -1},
     {-1, 2, 0, 2, -1},
     {-1, -1, 2, 0, 2},
     {-1, -1, -1, 2, 0}
   };

   int to_weights[5] = {1, 1, 1, 1, 1};
   int *to_matrix[5];
   for (int i = 0; i < 5; i++)
   {
      to_matrix[i] = to_edges[i];
   }
 
   Network to_network((int**)to_matrix, to_weights, 5);
   
   NetworkMapping mapping(&from_network, &to_network);
   mapping.m_mapping[0] = 0;
   mapping.m_mapping[1] = 4;
   int valid_links = mapping.valid_links();
   ASSERT_EQ(1, valid_links);
   valid_links = mapping.valid_links();
   ASSERT_EQ(1, valid_links);
}

TEST(LineNetwork, SameNodeValidMapping)
{
   int from_edges[2][2] = 
   {
      {0, 1},
      {1, 0}
   };
   int from_weights[2] = {1, 1};
   int *from_matrix[2];
   for (int i = 0; i < 2; i++)
   {
      from_matrix[i] = from_edges[i];
   }
 
   Network from_network((int**)from_matrix, from_weights, 2);


   int to_edges[5][5] =
   { 
     {0, 2, 0, 0, 0},
     {2, 0, 2, 0, 0},
     {0, 2, 0, 2, 0},
     {0, 0, 2, 0, 2},
     {0, 0, 0, 2, 0}
   };

   int to_weights[5] = {1, 2, 1, 1, 1};
   int *to_matrix[5];
   for (int i = 0; i < 5; i++)
   {
      to_matrix[i] = to_edges[i];
   }
 
   Network to_network((int**)to_matrix, to_weights, 5);
   
   NetworkMapping mapping(&from_network, &to_network);
   mapping.m_mapping[0] = 1;
   mapping.m_mapping[1] = 1;
   int valid_nodes = mapping.valid_nodes();
   ASSERT_EQ(2, valid_nodes);
   int valid_links = mapping.valid_links();
   ASSERT_EQ(1, valid_links);
}

TEST(LineNetwork, SameNodeInvalidMapping)
{
   int from_edges[2][2] = 
   {
      {0, 1},
      {1, 0}
   };
   int from_weights[2] = {1, 1};
   int *from_matrix[2];
   for (int i = 0; i < 2; i++)
   {
      from_matrix[i] = from_edges[i];
   }
 
   Network from_network((int**)from_matrix, from_weights, 2);


   int to_edges[5][5] =
   { 
     {0, 2, 0, 0, 0},
     {2, 0, 2, 0, 0},
     {0, 2, 0, 2, 0},
     {0, 0, 2, 0, 2},
     {0, 0, 0, 2, 0}
   };

   int to_weights[5] = {1, 1, 1, 1, 1};
   int *to_matrix[5];
   for (int i = 0; i < 5; i++)
   {
      to_matrix[i] = to_edges[i];
   }
 
   Network to_network((int**)to_matrix, to_weights, 5);
   
   NetworkMapping mapping(&from_network, &to_network);
   mapping.m_mapping[0] = 1;
   mapping.m_mapping[1] = 1;
   int valid_nodes = mapping.valid_nodes();
   ASSERT_EQ(1, valid_nodes);
   int valid_links = mapping.valid_links();
   ASSERT_EQ(1, valid_links);
}

TEST(LineNetwork, InvalidLinks)
{
   int from_edges[2][2] = 
   {
      {0, 5},
      {5, 0}
   };
   int from_weights[2] = {1, 1};
   int *from_matrix[2];
   for (int i = 0; i < 2; i++)
   {
      from_matrix[i] = from_edges[i];
   }
 
   Network from_network((int**)from_matrix, from_weights, 2);


   int to_edges[5][5] =
   { 
     {0, 2, -1, -1, -1},
     {2, 0, 2, -1, -1},
     {-1, 2, 0, 2, -1},
     {-1, -1, 2, 0, 2},
     {-1, -1, -1, 2, 0}
   };

   int to_weights[5] = {1, 1, 1, 1, 1};
   int *to_matrix[5];
   for (int i = 0; i < 5; i++)
   {
      to_matrix[i] = to_edges[i];
   }
 
   Network to_network((int**)to_matrix, to_weights, 5);
   
   NetworkMapping mapping(&from_network, &to_network);
   mapping.m_mapping[0] = 0;
   mapping.m_mapping[1] = 4;
   int valid_links = mapping.valid_links();
   ASSERT_EQ(0, valid_links);
}

TEST(LineNetwork, InvalidMapping)
{
   int edges[5][5] =
   { 
     {0, 2, -1, -1, -1},
     {2, 0, 2, -1, -1},
     {-1, 2, 0, 2, -1},
     {-1, -1, 2, 0, 2},
     {-1, -1, -1, 2, 0}
   };

   int *matrix[5];
   for (int i = 0; i < 5; i++)
   {
      matrix[i] = edges[i];
   }

   int nodes[] = {0,0,0,0,0};
   Network from_network((int**)matrix, nodes, 5);
   Network to_network((int**)matrix, nodes, 5);
   NetworkMapping mapping(&from_network, &to_network);
   mapping.m_mapping[0] = 1;
   mapping.m_mapping[1] = 2;
   mapping.m_mapping[2] = 4; 
   mapping.m_mapping[3] = 4;
   mapping.m_mapping[4] = 1;

   int valid_links = mapping.valid_links();

   ASSERT_EQ(3, valid_links);

}
int main(int argc, char **argv)
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

