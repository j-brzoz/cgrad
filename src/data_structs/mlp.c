#include "mlp.h"
#include "layer.h"
#include "value.h"
#include "input.h"
#include "../loss.h"
#include "../backward.h"
#include <stdio.h>
#include <stdlib.h>

// make the mlp
mlp_p make_mlp(size_t num_of_layers, size_t num_of_inputs, size_t *neurons_per_layer) {
	mlp_p m = malloc(sizeof(*m));
	if(m == NULL) {
		fprintf(stderr, "Failed to allocate memory for the mlp.");
		exit(EXIT_FAILURE);
	}
	m->num_of_layers = num_of_layers;
	m->num_of_inputs = num_of_inputs;
	m->neurons_per_layer = neurons_per_layer;
	m->layers = malloc(sizeof(layer_p) * num_of_layers);
	if(m->layers == NULL) {
                free(m);
		fprintf(stderr, "Failed to allocate memory for layers in the mlp.");
                exit(EXIT_FAILURE);
        }
	
	for(int i = 0; i < num_of_layers; i++) {
		if(i == 0) {
			m->layers[i] = make_layer(num_of_inputs, neurons_per_layer[0]);
		} else {
			m->layers[i] = make_layer(neurons_per_layer[i-1], neurons_per_layer[i]);
		}
	}
	return m;
}

// call the mlp
value_p* call_mlp(mlp_p m, double* inputs) {
	value_p* next_inputs;
	for(int i = 0; i < m->num_of_layers; i++) {
		if(i == 0) {
			next_inputs = call_first_layer(m->layers[i], inputs);
		} else {
			next_inputs = call_next_layer(m->layers[i], next_inputs);
		}
	}
	return next_inputs;
}

// train the mlp
void train_mlp(mlp_p m, size_t iterations, input_p input, output_p output, double learning_rate, size_t is_verbose) {	
	value_p* out_pred = malloc(sizeof(*out_pred) * output->num);
	if(out_pred == NULL) {
		fprintf(stderr, "Failed to allocate memory for predictions.");
		exit(EXIT_FAILURE);
	}
	value_p* tmp;
	value_p loss;
	
	for(int a = 0; a < iterations; a++) {	
		// forward pass
		for(int i = 0; i < output->num; i++) {
			tmp = call_mlp(m, input->data[i]);
			out_pred[i] = tmp[0];
			free(tmp);
		}
		
		loss = mean_sqr_error(out_pred, output->data, output->num);
	
		// backward
		for(int i = 0; i < m->num_of_layers; i++) {
			for(int j = 0; j < m->layers[i]->num_of_neurons; j++) {
				for(int k = 0; k < m->layers[i]->neurons[j]->num_of_inputs+1; k++) {
					m->layers[i]->neurons[j]->parameters[k]->gradient = 0.0;
				}
			}
		}
		backward(loss);

		// update
		for(int i = 0; i < m->num_of_layers; i++) {
			for(int j = 0; j < m->layers[i]->num_of_neurons; j++) {
				for(int k = 0; k < m->layers[i]->neurons[j]->num_of_inputs+1; k++) {
					m->layers[i]->neurons[j]->parameters[k]->data += -learning_rate * m->layers[i]->neurons[j]->parameters[k]->gradient;
				}
			}
		}
		
		if(is_verbose != 0) {
			printf("Iteration: %d Loss: ", a+1);
			print_value(loss);
		}

	}
	
	free(out_pred);
}

// free memory that had been allocated for the layer
void free_mlp(mlp_p m) {
	if(m != NULL) {
		if(m->neurons_per_layer != NULL) {
			free(m->neurons_per_layer);
		}
		if(m->layers != NULL) {
			for(int i = 0; i < m->num_of_layers; i++) {
				if(m->layers[i] != NULL) {
					free_layer(m->layers[i]);
				}
			}
			free(m->layers);
		}
		free(m);
	}
}
