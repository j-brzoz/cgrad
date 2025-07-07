#include "./data_structs/set.h"
#include "./ml_structs/value.h"
#include "./data_structs/array.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

extern val_array_p global_array;

// sorts all values in reverse topological order for backward pass
void reverse_topological_sort(value_p node, set_p visited, set_p rev_topo_ord) {
	if(node != NULL && check_if_in_set(visited, node->id) == 0) {
		add_2_set(visited, node->id);
		if(node->children != NULL) {
			for(int i = 0; i < node->children->num_of_elements; i++) {
				if(global_array->elements[node->children->elements[i]] != NULL){
					reverse_topological_sort(global_array->elements[node->children->elements[i]], visited, rev_topo_ord);
				}
			}
		}
		add_2_set(rev_topo_ord, node->id);
	}
}

// derivative for addition
void backward_add(value_p val) {
	if(val->children->num_of_elements == 2) { // a + b
		global_array->elements[val->children->elements[0]]->gradient += val->gradient;
		global_array->elements[val->children->elements[1]]->gradient += val->gradient;
	} else if(val->children->num_of_elements == 1) { // a + a
		global_array->elements[val->children->elements[0]]->gradient += 2 * val->gradient;
	} else {
		fprintf(stderr, "wrong number of children in addition");
		exit(EXIT_FAILURE);
	}
}

// derivative for multiplication
void backward_mul(value_p val) {
	if(val->children->num_of_elements == 2) { // a * b
		global_array->elements[val->children->elements[0]]->gradient += global_array->elements[val->children->elements[1]]->data * val->gradient;
		global_array->elements[val->children->elements[1]]->gradient += global_array->elements[val->children->elements[0]]->data * val->gradient;
	} else if(val->children->num_of_elements == 1) { // a * a
		global_array->elements[val->children->elements[0]]->gradient += 2 * global_array->elements[val->children->elements[0]]->data * val->gradient;
	} else {
		fprintf(stderr, "wrong number of children in multiplication");
		exit(EXIT_FAILURE);
	}
}

// derivative for power operation
void backward_pow(value_p val) { 
	if(val->children->num_of_elements == 2) { // a**b
		global_array->elements[val->children->elements[0]]->gradient += global_array->elements[val->children->elements[1]]->data * pow(global_array->elements[val->children->elements[0]]->data, global_array->elements[val->children->elements[1]]->data - 1.0) * val->gradient;
	} else {
		fprintf(stderr, "wrong number of children for power operation");
		exit(EXIT_FAILURE);
	}
}

// derivative for tanh operation
void backward_tanh(value_p val) {
	if(val->children->num_of_elements == 1) { // tanh(a)
		global_array->elements[val->children->elements[0]]->gradient += (1.0 - pow(val->data, 2)) * val->gradient;
	} else {
		fprintf(stderr, "wrong number of children for tanh operation");
		exit(EXIT_FAILURE);
	}
}

// derivative for exp operation
void backward_exp(value_p val) {
	if(val->children->num_of_elements == 1) { //e**a
		global_array->elements[val->children->elements[0]]->gradient += val->data * val->gradient;
	} else {
		fprintf(stderr, "wrong number of children for exp operation");
		exit(EXIT_FAILURE);
	}
}

// backward pass through all children
void backward(value_p val) {
	set_p visited = make_set_p();
	set_p rev_topo_ord = make_set_p();
	reverse_topological_sort(val, visited, rev_topo_ord);
	val->gradient = 1.0;
	for(int i = rev_topo_ord->num_of_elements - 1; i >= 0;  i--) {		
		if(global_array->elements[rev_topo_ord->elements[i]]->operation != NULL){
			if(strcmp(global_array->elements[rev_topo_ord->elements[i]]->operation, "sum") == 0) {
				backward_add(global_array->elements[rev_topo_ord->elements[i]]);
			} else if(strcmp(global_array->elements[rev_topo_ord->elements[i]]->operation, "mul") == 0) {
				backward_mul(global_array->elements[rev_topo_ord->elements[i]]);
			} else if(strcmp(global_array->elements[rev_topo_ord->elements[i]]->operation, "pow") == 0) {
				backward_pow(global_array->elements[rev_topo_ord->elements[i]]);
			} else if(strcmp(global_array->elements[rev_topo_ord->elements[i]]->operation, "tnh") == 0) {
				backward_tanh(global_array->elements[rev_topo_ord->elements[i]]);
			} else if(strcmp(global_array->elements[rev_topo_ord->elements[i]]->operation, "exp") == 0) {
				backward_exp(global_array->elements[rev_topo_ord->elements[i]]);
			} else {
				fprintf(stderr, "unknown operation");
				exit(EXIT_FAILURE);
			}	
		}
	}
	free_set(visited);
	free_set(rev_topo_ord);
}
