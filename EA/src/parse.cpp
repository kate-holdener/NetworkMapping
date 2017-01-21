#include "parse.h"

void parse_line(char *line, int *values, int *num_values)     
{
   char *c;
   char *start = line;
   int  values_size = *num_values;
   int  value = 0;
   *num_values = 0;

   // parse the line
   for (c = line; *c!='\0'; c++)
   {
      if (*c < '0' || *c > '9')
      {
         *c = '\0';
         if (c - start > 0)
         {
            value = atoi(start);
            values[*num_values] = value;
            (*num_values)++;
            if (*num_values == values_size)
            {
               break;
            }
         }
         start = c + 1;
       }
   } 
}

