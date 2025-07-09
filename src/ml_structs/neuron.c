#include "neuron.h"
#include "value.h"
#include <stdio.h>
#include <stdlib.h>

// make a neuron
neuron_p make_neuron(const size_t num_of_inputs) {
	double random = 0.0;
	value_p* parameters = malloc(sizeof(*parameters) * (num_of_inputs+1));
	if(parameters == NULL) {
		fprintf(stderr, "Failed to allocate the memory for neuron's parameters.");
		exit(EXIT_FAILURE);
	}

	for(size_t i = 0; i < num_of_inputs+1; i++) {
		random = ((double)rand() / RAND_MAX) * 2.0 - 1.0; // num between -1.0 and 1.0
		parameters[i] = make_value(random, 0.0, NULL, NULL); 
	}
	neuron_p out = malloc(sizeof(*out));
	if(out == NULL) {
               	free(parameters);
	       	fprintf(stderr, "Failed to allocate the memory for neuron's parameters.");
                exit(EXIT_FAILURE);
        }

	out->num_of_inputs = num_of_inputs;
	out->parameters = parameters;
	return out;
}

// call a neuron (inputs are doubles)
value_p call_double_neuron(const neuron_p n, const double* inputs) {
	value_p out = make_value(0.0, 0.0, NULL, NULL);
	for(size_t i = 0; i < n->num_of_inputs; i++) {
		value_p input = make_value(inputs[i], 0.0, NULL, NULL);
		value_p mul = mul_value(n->parameters[i], input);
		out = add_value(out, mul);
	}
	out = add_value(out, n->parameters[n->num_of_inputs]);
	out = tanh_value(out);
	return out;
}

// call a neuron (inputs are value_ps)
value_p call_value_neuron(const neuron_p n, const value_p* inputs) {
	value_p out = make_value(0.0, 0.0, NULL, NULL);
	for(size_t i = 0; i < n->num_of_inputs; i++) {
		value_p mul = mul_value(n->parameters[i], inputs[i]);
		out = add_value(out, mul);
	}
	out = add_value(out, n->parameters[n->num_of_inputs]);
	out = tanh_value(out);
	return out;
}

// free memory that had been allocated for the layer
void free_neuron(neuron_p n) {
	if(n != NULL) {
		if(n->parameters != NULL) {
			free(n->parameters);
		}
		free(n);
	}
}
