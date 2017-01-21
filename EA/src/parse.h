#include <stdlib.h>

/*
 * This function parses a character array that contains integers
 * and stores these integers in the integer array 'values'. The
 * number of integers stored is recorded in num_values.
 * @param line [IN] character array to parse
 * @param values [OUT] integer array containing parsed values
 * @param num_values [IN/OUT] number of integers recored into 'values' array
 */
void parse_line(char *line, int *values, int *num_values);
