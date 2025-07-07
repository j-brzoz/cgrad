#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include <stdio.h>

typedef struct layer {
	size_t num_of_inputs;   // number of inputs to neurons
	size_t num_of_neurons;  // number of neurons in the layer
	neuron_p* neurons;      // neurons
} layer_t, *layer_p;

// make a layer of neurons
layer_p make_layer(size_t num_of_inputs, size_t num_of_neurons);
// call first layer in mlp (inputs are doubles)
value_p* call_first_layer(layer_p l, double* inputs);
// call next layers in mlp (input are value_ps)
value_p* call_next_layer(layer_p l, value_p* inputs);
// free memory that had been allocated for the layer
void free_layer(layer_p l);

#endif
