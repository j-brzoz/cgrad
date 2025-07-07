#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

typedef struct input {
	size_t rows;		    // number of rows of data
	size_t row_length;      // number of elements in the singular row of data
	double** data;          // data
} input_t, *input_p;

// read data from external file
input_p read_input(FILE *f);
// free memory that had been allocated for input
void free_input(input_p in);

#endif
