#include "Initialization.h"
#include "Mutation.h"
#include "Crossover.h"
#include "Fitness.h"
#include "Competition.h"
#include "EAParameters.h"
#include <gtest/gtest.h>


TEST(EAParameters, ReadFromFile)
{
   EAParameters parameters;
   parameters.read_from_file("parameters1.txt");
   ASSERT_EQ(initialize_random, parameters.initialize); 
   ASSERT_EQ(mutate_random, parameters.mutate);
   ASSERT_EQ(crossover_random, parameters.crossover);
   ASSERT_EQ(nodes_and_links_ratio, parameters.evaluate);
   ASSERT_EQ(fittest_survive, parameters.compete);
   ASSERT_EQ(1234, parameters.population_size);
   EXPECT_FLOAT_EQ(0.95, parameters.mutation_rate);
}

int main(int argc, char**argv)
{
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
