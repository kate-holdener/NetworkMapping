#include "parse.h"

void parse_line(char *line, double *values, int *num_values)     
{
   char *start = line;
   char *end   = line;
   int  values_size = *num_values;
   double  value = 0;
   *num_values = 0;

   // parse the line
   while (*start != '\0')
   {
      if (*start >= '0' && *start <= '9')
      {
         value = strtod(start, &end);
         // conversion successful
         if (start != end)
         {
            values[*num_values] = value;
            (*num_values)++;
            if (*num_values == values_size)
            {
               break;
            }
         }
         // conversion failed
         else
         {
            break;
         }
         start = end;
       }
       else
       {
          start++;
       }
   }
}

