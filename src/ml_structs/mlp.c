#include "mlp.h"
#include "layer.h"
#include "value.h"
#include "../io/input.h"
#include "../loss.h"
#include "../backward.h"
#include <stdio.h>
#include <stdlib.h>

// make the mlp
mlp_p make_mlp(const size_t num_of_layers, const size_t num_of_inputs, size_t *neurons_per_layer) {
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
	
	for(size_t i = 0; i < num_of_layers; i++) {
		if(i == 0) {
			m->layers[i] = make_layer(num_of_inputs, neurons_per_layer[0]);
		} else {
			m->layers[i] = make_layer(neurons_per_layer[i-1], neurons_per_layer[i]);
		}
	}
	return m;
}

// call the mlp
value_p* call_mlp(const mlp_p m, const double* inputs) {
	value_p* next_inputs = NULL;
	for(size_t i = 0; i < m->num_of_layers; i++) {
		if(i == 0) {
			next_inputs = call_first_layer(m->layers[i], inputs);
		} else {
			next_inputs = call_next_layer(m->layers[i], next_inputs);
		}
	}
	return next_inputs;
}

// train the mlp
void train_mlp(mlp_p m, const size_t epochs, const input_p input, const output_p output, const double learning_rate, const size_t batch_size, const size_t is_verbose) {	
	value_p* out_pred = malloc(sizeof(*out_pred) * batch_size);
	if(out_pred == NULL) {
		fprintf(stderr, "Failed to allocate memory for predictions.");
		exit(EXIT_FAILURE);
	}

	value_p* tmp;
	value_p loss;
	
	for(size_t a = 0; a < epochs; a++) {	
        size_t iteration = 0;
        size_t start_sample;
        size_t end_sample;
        size_t current_batch_size;
		double total_epoch_loss = 0.0;
        size_t num_batches_in_epoch = 0;
		
		size_t global_id_state_before_batch_pass = *id;
		while (1) {
			start_sample = iteration * batch_size;
			if (start_sample >= output->num) {
                break;
            }
			end_sample = start_sample + batch_size;
            if (end_sample > output->num) {
                end_sample = output->num;
            }
			current_batch_size = end_sample - start_sample;

			// forward pass
			for(size_t i = start_sample; i < end_sample; i++) {
				tmp = call_mlp(m, input->data[i]);
				out_pred[i-start_sample] = tmp[0];
				free(tmp);
			}
			loss = mean_sqr_error(out_pred, (output->data)+start_sample, current_batch_size);
            total_epoch_loss += loss->data;
            num_batches_in_epoch++;

			// backward
			for(size_t i = 0; i < m->num_of_layers; i++) {
				for(size_t j = 0; j < m->layers[i]->num_of_neurons; j++) {
					for(size_t k = 0; k < m->layers[i]->neurons[j]->num_of_inputs+1; k++) {
						m->layers[i]->neurons[j]->parameters[k]->gradient = 0.0;
					}
				}
			}
			backward(loss);
	
			// update
			for(size_t i = 0; i < m->num_of_layers; i++) {
				for(size_t j = 0; j < m->layers[i]->num_of_neurons; j++) {
					for(size_t k = 0; k < m->layers[i]->neurons[j]->num_of_inputs+1; k++) {
						m->layers[i]->neurons[j]->parameters[k]->data += -learning_rate * m->layers[i]->neurons[j]->parameters[k]->gradient;
					}
				}
			}
			
			iteration++;
			
			// danger zone - messing with globals
			delete_elems_from_val_array(global_array, global_id_state_before_batch_pass);
			*id = global_id_state_before_batch_pass;
		}
		if(is_verbose != 0) {
			printf("Epoch: %ld Loss: %f\n", a+1, total_epoch_loss / iteration);
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
			for(size_t i = 0; i < m->num_of_layers; i++) {
				if(m->layers[i] != NULL) {
					free_layer(m->layers[i]);
				}
			}
			free(m->layers);
		}
		free(m);
	}
}
