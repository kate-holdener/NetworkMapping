#include <gtest/gtest.h>
#define private public
#include "EA.h"
#include "Network.h"

class EAFixture: public ::testing::Test
{
public:

EAFixture()
{
   double from_edges[2][2] = 
   {
      {0, 1},
      {1, 0}
   };
   double from_weights[2] = {1, 1};
   double *from_matrix[2];
   for (int i = 0; i < 2; i++)
   {
      from_matrix[i] = from_edges[i];
   }
 
   from_network = new Network((double**)from_matrix, from_weights, 2);


   double to_edges[5][5] =
   { 
     {0, 2, 0, 0, 0},
     {2, 0, 2, 0, 0},
     {0, 2, 0, 2, 0},
     {0, 0, 2, 0, 2},
     {0, 0, 0, 2, 0}
   };

   double to_weights[5] = {2, 2, 2, 2, 2};
   double *to_matrix[5];
   for (int i = 0; i < 5; i++)
   {
      to_matrix[i] = to_edges[i];
   }
 
   to_network = new Network((double**)to_matrix, to_weights, 5);
 
}

virtual ~EAFixture()
{
   delete to_network;
   delete from_network;
}

Network *from_network;
Network *to_network;
};


TEST_F(EAFixture, Initialize)
{
   EA ea(from_network, to_network);
   ea.initialize();
   ASSERT_EQ(200, ea.m_population.m_pool_size);
   for (int i = 0; i < 100; i++)
   {
      ASSERT_EQ(2, ea.m_population.m_parents[i]->m_solution.valid_nodes());
      ASSERT_EQ(1, ea.m_population.m_parents[i]->m_solution.valid_links());
   }
}

TEST_F(EAFixture, Evaluate)
{
   EA ea(from_network, to_network);
   ea.initialize();
   (*ea._evaluate)(ea.m_population.m_parents, ea.m_population.m_num_parents);
   for (int i = 0; i < ea.m_population_size; i++)
   {
      ASSERT_DOUBLE_EQ(2, ea.m_population.m_parents[i]->m_fitness);
   }
}


TEST_F(EAFixture, SetPopulationSize)
{
   EA ea(from_network, to_network);
   ea.set_population_size(10);
   ea.initialize();
   ASSERT_EQ(10, ea.m_population_size);
   ASSERT_EQ(10, ea.m_population.m_num_parents);
}

TEST_F(EAFixture, SetMutationRate)
{
   EA ea(from_network, to_network);
   ea.set_mutation_rate(0.1);
   ea.initialize();
   ASSERT_FLOAT_EQ(0.1, ea.m_mutation_rate);
   ASSERT_EQ(10, ea.m_mutation_percent);
}

TEST_F(EAFixture, Crossover)
{
   EA ea(from_network, to_network);
   ea.set_population_size(2);
   ea.initialize();

   ea.m_population.m_parents[0]->m_solution.m_mapping[0] = 2;
   ea.m_population.m_parents[0]->m_solution.m_mapping[1] = 2;
   ea.m_population.m_parents[1]->m_solution.m_mapping[0] = 5;
   ea.m_population.m_parents[1]->m_solution.m_mapping[1] = 5; 

   ea.m_population.m_selected_parents[0] = ea.m_population.m_parents[0];
   ea.m_population.m_selected_parents[1] = ea.m_population.m_parents[1];
   (*ea._crossover)(&ea.m_population); 

   for (int i = 0; i < 2; i++)
   {
      if (ea.m_population.m_offspring[i]->m_solution.m_mapping[0] == 2)
      {
         ASSERT_EQ(5, ea.m_population.m_offspring[i]->m_solution.m_mapping[1]);
      }
      else
      {
         ASSERT_EQ(2, ea.m_population.m_offspring[i]->m_solution.m_mapping[1]);
      }
   } 
}

TEST_F(EAFixture, Mutation)
{
   EA ea(from_network, to_network);
   ea.set_population_size(2);
   ea.set_mutation_rate(1);
   ea.initialize();
   ea.m_population.m_parents[0]->m_solution.m_mapping[0] = 5;
   ea.m_population.m_parents[0]->m_solution.m_mapping[1] = 5;
   ea.m_population.m_parents[1]->m_solution.m_mapping[0] = 5;
   ea.m_population.m_parents[1]->m_solution.m_mapping[1] = 5; 

   // fake out selection
   ea.m_population.m_parents[0]->m_solution.m_mapping[0] = 2;
   ea.m_population.m_parents[0]->m_solution.m_mapping[1] = 2;
 
   (*ea._crossover)(&ea.m_population);   
   ea.mutate();
   for (int i = 0; i < 2; i++)
   {
      ASSERT_TRUE(ea.m_population.m_offspring[i]->m_solution.m_mapping[0] != 5 ||
                  ea.m_population.m_offspring[i]->m_solution.m_mapping[1] != 5);
   }
}

TEST_F(EAFixture, NoMutation)
{
   EA ea(from_network, to_network);
   ea.set_population_size(2);
   ea.set_mutation_rate(0);
   ea.initialize();
   ea.m_population.m_parents[0]->m_solution.m_mapping[0] = 5;
   ea.m_population.m_parents[0]->m_solution.m_mapping[1] = 5;
   ea.m_population.m_parents[1]->m_solution.m_mapping[0] = 5;
   ea.m_population.m_parents[1]->m_solution.m_mapping[1] = 5; 

   ea.m_population.m_selected_parents[0] = ea.m_population.m_parents[0];
   ea.m_population.m_selected_parents[1] = ea.m_population.m_parents[1];
   (*ea._crossover)(&ea.m_population);   
   ea.mutate();
   for (int i = 0; i < 2; i++)
   {
      ASSERT_EQ(5, ea.m_population.m_offspring[i]->m_solution.m_mapping[0]);
      ASSERT_EQ(5, ea.m_population.m_offspring[i]->m_solution.m_mapping[1]);
   }
}

TEST_F(EAFixture, Compete)
{
   EA ea(from_network, to_network);
   ea.set_population_size(4);
   ea.initialize();
   (*ea._evaluate)(ea.m_population.m_parents, ea.m_population.m_num_parents);

   // fake out selection
   ea.m_population.m_selected_parents[0] = ea.m_population.m_parents[0];
   ea.m_population.m_selected_parents[1] = ea.m_population.m_parents[1];
   ea.m_population.m_selected_parents[2] = ea.m_population.m_parents[2];
   ea.m_population.m_selected_parents[3] = ea.m_population.m_parents[3];

   (*ea._crossover)(&ea.m_population);
   ea.m_population.m_offspring[0]->m_fitness = 0;
   ea.m_population.m_offspring[1]->m_fitness = 4;
   ea.m_population.m_offspring[2]->m_fitness = 1;
   ea.m_population.m_offspring[3]->m_fitness = 2.5;
   (*ea._compete)(&ea.m_population);
   ASSERT_DOUBLE_EQ(4, ea.m_population.m_parents[0]->m_fitness);
   ASSERT_DOUBLE_EQ(2.5, ea.m_population.m_parents[1]->m_fitness);
   ASSERT_DOUBLE_EQ(2, ea.m_population.m_parents[2]->m_fitness);
   ASSERT_DOUBLE_EQ(2, ea.m_population.m_parents[3]->m_fitness);
 
}

int main(int argc, char **argv)
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

