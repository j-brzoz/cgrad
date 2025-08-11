#include "output.h"
#include <stdio.h>
#include <stdlib.h>

// read data from external file
output_p read_output(FILE * const f) {
	output_p out = malloc(sizeof(*out));
	if(out == NULL) {
		fprintf(stderr, "Failed to allocate memory for output");
                exit(EXIT_FAILURE);
	}

	if(fscanf(f, "%zu", &(out->rows)) != 1 ) {
		free(out);
		fprintf(stderr, "Failed to get output info");
                exit(EXIT_FAILURE);
	}
	
	out->data = malloc(sizeof(value_p) * out->rows);
	if(out->data == NULL) {
		fprintf(stderr, "Failed to allocate memory for output data");
        	free(out);
		exit(EXIT_FAILURE);
	}
	
	double tmp;
	for(size_t i = 0; i < out->rows; i++) {
		if( fscanf( f, "%lf", &(tmp) ) != 1 ) {
			fprintf(stderr, "Failed to get output data");
			free(out->data);
			free(out);
			exit(EXIT_FAILURE);
		} else {
			out->data[i] = make_value(tmp, 0.0, NULL, NULL);
		}
	}

	return out;
}

// compute input statistic
void get_stats_output(output_p output) {
	output->mean = 0.0;
	output->std = 0.0;

	// calculate mean
	for (size_t i = 0; i < output->rows; i++) {
		output->mean += output->data[i]->data;
	}
	output->mean /= output->rows;

	// calculate std
	for (size_t i = 0; i < output->rows; i++) {
		output->std += (output->data[i]->data - output->mean) * (output->data[i]->data - output->mean);
	}
	output->std /= output->rows;
	output->std = sqrt(output->std);
}

// scale input accoring to statistics
void scale_output(output_p output) {
	for (size_t i = 0; i < output->rows; i++) {
		output->data[i]->data = (output->data[i]->data - output->mean) / output->std;
	}
}

// free memory that had been allocated for the output
void free_output(output_p out) {
	if(out != NULL) {
		if(out->data != NULL) {
			free(out->data);
		}
        	free(out);
	}
}
