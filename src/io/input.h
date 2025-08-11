#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <math.h>

typedef struct input {
	size_t rows;		    // number of rows of data
	size_t row_length;      // number of elements in the singular row of data
	double** data;          // data
	double* mean;			// mean of each feature
	double* std;			// std of each feature
} input_t, *input_p;

// read data from external file
input_p read_input(FILE * const f);
// compute input statistic
void get_stats_input(input_p input);
// scale input accoring to statistics
void scale_input(input_p input);
// free memory that had been allocated for input
void free_input(input_p in);

#endif
