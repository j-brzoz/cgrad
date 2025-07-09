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

// free memory that had been allocated for input
void free_input(const input_p in) {
	if(in != NULL) {
		if(in->data != NULL) {
			for(size_t i = 0; i < in->rows; i++) {
        			if(in->data[i] != NULL) {
					free(in->data[i]);
				}
       			}	
			free(in->data);
		}
        	free(in);
	}
}
