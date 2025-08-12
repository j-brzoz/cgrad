#include "neuron.h"
#include "layer.h"
#include <stdio.h>
#include <stdlib.h>

// make a layer of neurons
layer_p make_layer(const size_t num_of_inputs, const size_t num_of_neurons) {
	layer_p out = malloc(sizeof(*out));
	if(out == NULL) {
		fprintf(stderr, "Failed to allocate memory for a layer.");
		exit(EXIT_FAILURE);
	}
	out->num_of_inputs = num_of_inputs;
	out->num_of_neurons = num_of_neurons;
	out->neurons = malloc(sizeof(neuron_p) * num_of_neurons);
	if(out->neurons == NULL) {
		free(out);
		fprintf(stderr, "Failed to allocate memory for neurons in a layer.");
                exit(EXIT_FAILURE);
	}
	for(size_t i = 0; i < num_of_neurons; i++) {
		out->neurons[i] = make_neuron(num_of_inputs, num_of_neurons);
	}
	return out;
}

// call first layer in mlp (inputs are doubles)
value_p* call_first_layer(const layer_p l, const double* inputs) {
	value_p* out = malloc(sizeof(*out) * l->num_of_neurons);
	if(out == NULL) {
                fprintf(stderr, "Failed to allocate memory for output from the first layer.");
                exit(EXIT_FAILURE);
        }
	for(size_t i = 0; i < l->num_of_neurons; i++) {
		out[i] = call_double_neuron(l->neurons[i], inputs);
	}
	return out;
}

// call next layers in mlp (input are value_ps)
value_p* call_next_layer(const layer_p l, value_p* inputs, const size_t is_last_layer) {
	value_p* out = malloc(sizeof(*out) * l->num_of_neurons);
	if(out == NULL) {
                fprintf(stderr, "Failed to allocate memory for output from next layers.");
                exit(EXIT_FAILURE);
        }
	for(size_t i = 0; i < l->num_of_neurons; i++) {
		out[i] = call_value_neuron(l->neurons[i], inputs, is_last_layer);
	}
	if(inputs != NULL) {
		free(inputs);
	}
	return out;
}



// free memory that had been allocated for the layer
void free_layer(layer_p l) {
	if(l != NULL ) {
		if(l->neurons != NULL) {	
			for(size_t i = 0; i < l->num_of_neurons; i++) {
				if(l->neurons[i] != NULL) {
					free_neuron(l->neurons[i]);
				}
			}
			free(l->neurons);
		}
		free(l);
	}
}
