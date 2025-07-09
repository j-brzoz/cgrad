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

	if(fscanf(f, "%zu", &(out->num)) != 1 ) {
		free(out);
		fprintf(stderr, "Failed to get output info");
                exit(EXIT_FAILURE);
	}
	
	out->data = malloc(sizeof(value_p) * out->num);
	if(out->data == NULL) {
		fprintf(stderr, "Failed to allocate memory for output data");
        	free(out);
		exit(EXIT_FAILURE);
	}
	
	double tmp;
	for(size_t i = 0; i < out->num; i++) {
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

// free memory that had been allocated for the output
void free_output(const output_p out) {
	if(out != NULL) {
		if(out->data != NULL) {
			free(out->data);
		}
        	free(out);
	}
}
