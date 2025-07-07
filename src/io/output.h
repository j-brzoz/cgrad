#ifndef OUTPUT_H
#define OUTPUT_H

#include "../ml_structs/value.h"
#include <stdio.h>

typedef struct output {
	size_t num;     // number of outputs
	value_p* data;  // outputs
} output_t, *output_p;

// read data from external file
output_p read_output(FILE *f);
// free memory that had been allocated for the output
void free_output(output_p out);

#endif
