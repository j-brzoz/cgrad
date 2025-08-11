#ifndef OUTPUT_H
#define OUTPUT_H

#include "../ml_structs/value.h"
#include <stdio.h>
#include <math.h>

typedef struct output {
	size_t rows;     		// number of outputs
	value_p* data;  		// outputs
	double mean;			// mean of outputs
	double std;				// std of outputs
} output_t, *output_p;

// read data from external file
output_p read_output(FILE * const f);
// compute output statistic
void get_stats_output(output_p output);
// scale output accoring to statistics
void scale_output(output_p output);
// free memory that had been allocated for the output
void free_output(output_p out);

#endif
