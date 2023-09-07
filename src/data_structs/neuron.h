#ifndef NEURON_H
#define NEURON_H

#include "../data_structs/value.h"
#include <stdio.h>

typedef struct neuron {
	size_t num_of_inputs; // number of parameters = num_of_inputs + 1
	value_p* parameters;  // all parameters (weights + bias); bias is the last parameter
} neuron_t, *neuron_p;

// make a neuron
neuron_p make_neuron(size_t num_of_inputs);
// call a neuron (inputs are doubles)
value_p call_double_neuron(neuron_p n, double* inputs);
// call a neuron (inputs are value_ps)
value_p call_value_neuron(neuron_p n, value_p* inputs);
// free memory that had been allocated for the layer
void free_neuron(neuron_p n);

#endif
