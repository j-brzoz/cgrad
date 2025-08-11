#include "input.h"
#include <stdio.h>
#include <stdlib.h>

// read data from external file
input_p read_input(FILE * const f) {
	input_p in = malloc(sizeof(*in));
	if(in == NULL) {
		fprintf(stderr, "Failed to allocate memory for input");
		exit(EXIT_FAILURE);
	}

	if(fscanf(f, "%zu %zu", &(in->rows), &(in->row_length)) != 2 ) {
		free(in);
		fprintf(stderr, "Failed to get input info");
		exit(EXIT_FAILURE);
	}

	in->data = malloc(sizeof(double*) * in->rows);
	if(in->data == NULL) {
		fprintf(stderr, "Failed to allocate memory for input data");
		free(in);
		exit(EXIT_FAILURE);
	}

	for(size_t i = 0; i < in->rows; i++) {
		in->data[i] = malloc(sizeof(double) * in->row_length);
		if(in->data[i] == NULL) {
			for(size_t j = 0; j < i; j++) {
				free(in->data[j]);
			}
			free(in->data);
			free(in);
			fprintf(stderr, "Failed to allocate memory for input data");
			exit(EXIT_FAILURE);
		}
	}

	for(size_t i = 0; i < in->rows; i++) {
		for(size_t j = 0; j < in->row_length; j++) {
			if( fscanf( f, "%lf", &(in->data[i][j]) ) != 1 ) {
				fprintf(stderr, "Failed to get input data");
				for(size_t k = 0; k < in->rows; k++) {
					free(in->data[k]);
				}
				free(in->data);
				free(in);
				exit(EXIT_FAILURE);
			}
		}
	}

	return in;
}

// compute input statistic
void get_stats_input(input_p input) {
	input->mean = malloc(sizeof(double) * input->row_length);
	input->std = malloc(sizeof(double) * input->row_length);
	if (input->mean == NULL || input->std == NULL) {
		free(input);			
		fprintf(stderr, "Failed to allocate memory for input statistics");
        exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < input->row_length; i++) {
		input->mean[i] = 0.0;
		input->std[i] = 0.0;
	}

	// calculate mean
	for (size_t i = 0; i < input->rows; i++) {
		for (size_t j = 0; j < input->row_length; j++) {
			input->mean[j] += input->data[i][j];
		}
	}
	for (size_t i = 0; i < input->row_length; i++) {
		input->mean[i] /= input->rows;
	}

	// calculate std
	for (size_t i = 0; i < input->rows; i++) {
		for (size_t j = 0; j < input->row_length; j++) {
			input->std[j] += (input->data[i][j] - input->mean[j]) * (input->data[i][j] - input->mean[j]);
		}
	}
	for (size_t i = 0; i < input->row_length; i++) {
		input->std[i] /= input->rows;
		input->std[i] = sqrt(input->std[i]);
	}
}

// scale input accoring to statistics
void scale_input(input_p input) {
	for (size_t i = 0; i < input->rows; i++) {
		for (size_t j = 0; j < input->row_length; j++) {
			input->data[i][j] = (input->data[i][j] - input->mean[j]) / input->std[j];
		}
	}
}

// free memory that had been allocated for input
void free_input(input_p in) {
	if(in != NULL) {
		if(in->data != NULL) {
			for(size_t i = 0; i < in->rows; i++) {
				if(in->data[i] != NULL) {
					free(in->data[i]);
				}
			}
			free(in->data);
		}
		if (in->mean != NULL) {
			free(in->mean);
		}
		if (in->std != NULL) {
			free(in->std);
		}
		free(in);
	}
}
