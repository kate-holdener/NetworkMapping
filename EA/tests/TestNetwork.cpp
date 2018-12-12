#include <gtest/gtest.h>
#include <string>
#define private public
#include "Network.h"
using namespace std;

char *input_dir = NULL;

TEST(LineNetwork, PathExists)
{
   double edges[5][5] =
   { 
     {-1, 2, -1, -1, -1},
     {2, -1, 2, -1, -1},
     {-1, 2, -1, 2, -1},
     {-1, -1, 2, -1, 2},
     {-1, -1, -1, 2, -1}
   };

   double weights[5] = {1, 1, 1, 1, 1};
   double *matrix[5];
   for (int i = 0; i < 5; i++)
   {
      matrix[i] = edges[i];
   }
 
   Network network((double**)matrix, weights, 5);
   ASSERT_EQ(true, network.path_exists(0, 4, 2));
}


TEST(LineNetwork, PathDoesNotExist)
{
   double edges[5][5] =
   { 
     {-1, 2, -1, -1, -1},
     {2, -1, 2, -1, -1},
     {-1, 2, -1, -1, -1},
     {-1, -1, -1, -1, 2},
     {-1, -1, -1, 2, -1}
   };

   double weights[5] = {1, 1, 1, 1, 1};
   double *matrix[5];
   for (int i = 0; i < 5; i++)
   {
      matrix[i] = edges[i];
   }
 
   Network network((double**)matrix, weights, 5);
   ASSERT_EQ(false, network.path_exists(0, 4, 2));
}

/*
 * Given a 5 node network that is:
 * 0 -- 1 -- 2 -- 3 -- 4, where the weight of each edge is 2,
 * calls reduce_capacity to reduce the capacity of path from 0 to 4 by 1
 */
TEST(LineNetwork, ReduceCapacity)
{
   double edges[5][5] =
   { 
     {-1, 2, -1, -1, -1},
     {2, -1, 2, -1, -1},
     {-1, 2, -1, 2, -1},
     {-1, -1, 2, -1, 2},
     {-1, -1, -1, 2, -1}
   };

   double weights[5] = {1, 1, 1, 1, 1};
   double *matrix[5];
   for (int i = 0; i < 5; i++)
   {
      matrix[i] = edges[i];
   }

   Network network((double**)matrix, weights, 5);
   int node_ancestor[5] = {-1, 0, 1, 2, 3};
   network.reduce_capacity(0, 4, node_ancestor, 1);

   for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < 5; j++)
      {
         if (i == j+1 || j == i+1)
         {
            ASSERT_EQ(network.m_link_weights[i][j], 1);
         }
         else
         {
            ASSERT_EQ(network.m_link_weights[i][j], -1);
         }
      }
   }
}

TEST(LineNetwork, EmbedExistingPath)
{
   double edges[5][5] =
   { 
     {-1, 3, -1, -1, -1},
     {3, -1, 3, -1, -1},
     {-1, 3, -1, 3, -1},
     {-1, -1, 3, -1, 3},
     {-1, -1, -1, 3, -1}
   };

   double weights[5] = {1, 1, 1, 1, 1};
   double *matrix[5];
   for (int i = 0; i < 5; i++)
   {
      matrix[i] = edges[i];
   }
 
   Network network((double**)matrix, weights, 5);
   // verify that the path can get embedded
   ASSERT_EQ(true, network.embed_path(0, 4, 2));

   // verify that capacity of network has been reduced appropriatelly
   for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < 5; j++)
      {
         if (i == j+1 || j == i+1)
         {
            ASSERT_EQ(network.m_link_weights[i][j], 1);
         }
         else
         {
            ASSERT_EQ(network.m_link_weights[i][j], -1);
         }
      }
   }

}

// tests to see that EmbedSameNodePath returns true and does not
// reduce network link capacity
TEST(LineNetwork, EmbedSameNodePath)
{
   double edges[5][5] =
   { 
     {-1, 2, -1, -1, -1},
     {2, -1, 2, -1, -1},
     {-1, 2, -1, 2, -1},
     {-1, -1, 2, -1, 2},
     {-1, -1, -1, 2, -1}
   };

   double weights[5] = {1, 1, 1, 1, 1};
   double *matrix[5];
   for (int i = 0; i < 5; i++)
   {
      matrix[i] = edges[i];
   }
 
   Network network((double**)matrix, weights, 5);
   ASSERT_EQ(true, network.embed_path(3, 3, 2));

   // verify that capacity of network has not changed
   for (int i = 0; i < 5; i++)
   {
      for (int j = 0; j < 5; j++)
      {
         if (i == j+1 || j == i+1)
         {
            ASSERT_EQ(network.m_link_weights[i][j], 2);
         }
         else
         {
            ASSERT_EQ(network.m_link_weights[i][j], -1);
         }
      }
   }

}


TEST(LineNetwork, EmbedNonExistingPath)
{
   double edges[5][5] =
   { 
     {-1, 3, -1, -1, -1},
     {3, -1, 3, -1, -1},
     {-1, 3, -1, -1, -1},
     {-1, -1, -1, -1, 3},
     {-1, -1, -1, 3, -1}
   };

   double weights[5] = {1, 1, 1, 1, 1};
   double *matrix[5];
   for (int i = 0; i < 5; i++)
   {
      matrix[i] = edges[i];
   }
 
   Network network((double**)matrix, weights, 5);
   // verify that the path can get embedded
   ASSERT_EQ(false, network.embed_path(0, 4, 2));

   // verify that capacity of network has not changed
   ASSERT_EQ(-1, network.m_link_weights[0][0]);
   ASSERT_EQ(3, network.m_link_weights[0][1]);
   ASSERT_EQ(-1, network.m_link_weights[0][2]);
   ASSERT_EQ(-1, network.m_link_weights[0][3]);
   ASSERT_EQ(-1, network.m_link_weights[0][4]);

   ASSERT_EQ(3, network.m_link_weights[1][0]);
   ASSERT_EQ(-1, network.m_link_weights[1][1]);
   ASSERT_EQ(3, network.m_link_weights[1][2]);
   ASSERT_EQ(-1, network.m_link_weights[1][3]);
   ASSERT_EQ(-1, network.m_link_weights[1][4]);

   ASSERT_EQ(-1, network.m_link_weights[2][0]);
   ASSERT_EQ(3, network.m_link_weights[2][1]);
   ASSERT_EQ(-1, network.m_link_weights[2][2]);
   ASSERT_EQ(-1, network.m_link_weights[2][3]);
   ASSERT_EQ(-1, network.m_link_weights[2][4]);

   ASSERT_EQ(-1, network.m_link_weights[3][0]);
   ASSERT_EQ(-1, network.m_link_weights[3][1]);
   ASSERT_EQ(-1, network.m_link_weights[3][2]);
   ASSERT_EQ(-1, network.m_link_weights[3][3]);
   ASSERT_EQ(3, network.m_link_weights[3][4]);

   ASSERT_EQ(-1, network.m_link_weights[4][0]);
   ASSERT_EQ(-1, network.m_link_weights[4][1]);
   ASSERT_EQ(-1, network.m_link_weights[4][2]);
   ASSERT_EQ(3, network.m_link_weights[4][3]);
   ASSERT_EQ(-1, network.m_link_weights[4][4]);

}

TEST(LineNetwork, PathExistsZeroWeight)
{
   double edges[5][5] =
   { 
     {-1, 0, -1, -1, -1},
     {0, -1, 0, -1, -1},
     {-1, 0, -1, 0, -1},
     {-1, -1, 0, -1, 0},
     {-1, -1, -1, 0, -1}
   };

   double weights[5] = {1, 1, 1, 1, 1};
   double *matrix[5];
   for (int i = 0; i < 5; i++)
   {
      matrix[i] = edges[i];
   }
 
   Network network((double**)matrix, weights, 5);
   ASSERT_EQ(true, network.path_exists(0, 4, 0));
}

TEST(ConstructorFromFile, InitSize)
{
   string input_file_name = input_dir;
   input_file_name.append("/test_network1.txt");
   FILE *input_file = fopen(input_file_name.c_str(), "r");
   Network network(input_file);
   fclose(input_file);
   ASSERT_EQ(5, network.m_size);
}

TEST(ConstructorFromFile, AdjacencyMatrix)
{
   string input_file_name = input_dir;
   input_file_name.append("/test_network1.txt");
   FILE *input_file = fopen(input_file_name.c_str(), "r");
   Network network(input_file);
   fclose(input_file);
   //verify that the weights are correct
   ASSERT_EQ(-1, network.m_link_weights[0][0]);
   ASSERT_EQ(1, network.m_link_weights[0][1]);
   ASSERT_EQ(-1, network.m_link_weights[0][2]);
   ASSERT_EQ(-1, network.m_link_weights[0][3]);
   ASSERT_EQ(-1, network.m_link_weights[0][4]);

   ASSERT_EQ(1, network.m_link_weights[1][0]);
   ASSERT_EQ(-1, network.m_link_weights[1][1]);
   ASSERT_EQ(0, network.m_link_weights[1][2]);
   ASSERT_EQ(-1, network.m_link_weights[1][3]);
   ASSERT_EQ(-1, network.m_link_weights[1][4]);

   ASSERT_EQ(-1, network.m_link_weights[2][0]);
   ASSERT_EQ(0, network.m_link_weights[2][1]);
   ASSERT_EQ(-1, network.m_link_weights[2][2]);
   ASSERT_EQ(2, network.m_link_weights[2][3]);
   ASSERT_EQ(-1, network.m_link_weights[2][4]);

   ASSERT_EQ(-1, network.m_link_weights[3][0]);
   ASSERT_EQ(-1, network.m_link_weights[3][1]);
   ASSERT_EQ(2, network.m_link_weights[3][2]);
   ASSERT_EQ(-1, network.m_link_weights[3][3]);
   ASSERT_EQ(30, network.m_link_weights[3][4]);

   ASSERT_EQ(-1, network.m_link_weights[4][0]);
   ASSERT_EQ(-1, network.m_link_weights[4][1]);
   ASSERT_EQ(-1, network.m_link_weights[4][2]);
   ASSERT_EQ(30, network.m_link_weights[4][3]);
   ASSERT_EQ(-1, network.m_link_weights[4][4]);

}

TEST(ConstructorFromFile, NodeWeights)
{
   string input_file_name = input_dir;
   input_file_name.append("/test_network1.txt");
   FILE *input_file = fopen(input_file_name.c_str(), "r");
   Network network(input_file);
   fclose(input_file);
   ASSERT_EQ(0, network.m_node_weights[0]);
   ASSERT_EQ(6, network.m_node_weights[1]);
   ASSERT_EQ(5, network.m_node_weights[2]);
   ASSERT_EQ(4, network.m_node_weights[3]);
   ASSERT_EQ(10, network.m_node_weights[4]);
}

int main(int argc, char **argv)
{
   if(argc < 2)
   {
      fprintf(stderr, "USAGE: ./<TestName> <input_dir>\n");
   }
   input_dir = argv[1];   
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


