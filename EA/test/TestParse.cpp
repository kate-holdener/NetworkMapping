
#include "parse.h"
#include <string>
#include <gtest/gtest.h>

TEST(Parser, ThreeValues)
{
   int values[3];
   int num_values = 3;
   std::string line = "123   456	789\n";
   char line_char[512];
   strncpy(line_char, line.c_str(), 512);  
   parse_line(line_char, values, &num_values);
   ASSERT_EQ(3, num_values);
   ASSERT_EQ(123, values[0]);
   ASSERT_EQ(456, values[1]);
   ASSERT_EQ(789, values[2]);
}

TEST(Parser, TwoValues)
{
   int values[3];
   int num_values = 2;
   std::string line = "123   456	789\n";
   char line_char[512];
   strncpy(line_char, line.c_str(), 512);  
   parse_line(line_char, values, &num_values);
   ASSERT_EQ(2, num_values);
   ASSERT_EQ(123, values[0]);
   ASSERT_EQ(456, values[1]);
}

TEST(Parser, OneValue)
{
   int values[1];
   int num_values = 1;
   std::string line = "123  \n";
   char line_char[512];
   strncpy(line_char, line.c_str(), 512);  
   parse_line(line_char, values, &num_values);
   ASSERT_EQ(1, num_values);
   ASSERT_EQ(123, values[0]);
}

TEST(Parser, OneValueLongArray)
{
   int values[3];
   int num_values = 3;
   std::string line = "123\n";
   char line_char[512];
   strncpy(line_char, line.c_str(), 512);  
   parse_line(line_char, values, &num_values);
   ASSERT_EQ(1, num_values);
   ASSERT_EQ(123, values[0]);
}


