#ifndef MLP_H
#define MLP_H

#include "layer.h"
#include "../io/input.h"
#include "../io/output.h"
#include "value.h"
#include <stdio.h>

typedef struct mlp {
	size_t num_of_layers;      // number of layers in the mlp
	size_t num_of_inputs;      // number of inputs fed into mlp
	size_t* neurons_per_layer; // number of neurons per layer
	layer_p* layers;           // layers
} mlp_t, *mlp_p;

// make the mlp
mlp_p make_mlp(const size_t num_of_layers, const size_t num_of_inputs, size_t *neurons_per_layer);
// call the mlp
value_p* call_mlp(const mlp_p m, const double* inputs);
// train the mlp
void train_mlp(mlp_p m, const size_t iterations, const input_p input, const output_p output, const double learning_rate, const size_t is_verbose);
// free memory that had been allocated for the mlp
void free_mlp(mlp_p m);

#endif
