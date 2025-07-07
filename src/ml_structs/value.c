#include "value.h"
#include "../data_structs/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern size_t* id;
extern val_array_p global_array;

// make a value
value_p make_value(double data, double gradient, char* operation, set_p children) {
	if(global_array == NULL) {
		global_array = make_val_array();
	}
	if(id == NULL) {
		id = malloc(sizeof(size_t));
		if(id == NULL) {
			fprintf(stderr, "Failed to allocate memory for id.");
			exit(EXIT_FAILURE);
		}
		*id = 0;
	}
	else {
		*id += 1;	
	}

	value_p out = malloc(sizeof(*out));
	if(out == NULL) {
        	fprintf(stderr, "Failed to allocate memory for value.");
                exit(EXIT_FAILURE);
        }
	out->id = *id;
	out->data = data;
	out->gradient = gradient;
	out->operation = operation;	
	out->children = children;
	add_2_val_array(global_array, out);
	return out;
}

// print value's data
void print_value(value_p val) {
	printf("Value(data=%f)\n", val->data);
}

// add two values
value_p add_value(value_p val1, value_p val2) {
	char* operation = malloc(sizeof(*operation) * 4);
	if(operation == NULL) {
                fprintf(stderr, "Failed to allocate memory for value's operation.");
                exit(EXIT_FAILURE);
        }
	strcpy(operation, "sum");	
	set_p children = make_set_p();
	add_2_set(children, val1->id);
	add_2_set(children, val2->id);
	value_p out = make_value(val1->data + val2->data, 0.0, operation, children);
	return out;
}

// multiply two values
value_p mul_value(value_p val1, value_p val2) {
	char* operation = malloc(sizeof(*operation) * 4);
	if(operation == NULL) {
                fprintf(stderr, "Failed to allocate memory for value's operation.");
                exit(EXIT_FAILURE);
        }
	strcpy(operation, "mul");	
	set_p children = make_set_p();
	add_2_set(children, val1->id);
	add_2_set(children, val2->id);
	value_p out = make_value(val1->data * val2->data, 0.0, operation, children);
	return out;
}

// raise value to the power
value_p pow_value(value_p val, double power) { // only supports float powers
	char* operation = malloc(sizeof(*operation) * 4);
	if(operation == NULL) {
                fprintf(stderr, "Failed to allocate memory for value's operation.");
                exit(EXIT_FAILURE);
        }
	strcpy(operation, "pow");	
	set_p children = make_set_p();
	value_p power_val = make_value(power, 0.0, NULL, NULL); 
	add_2_set(children, val->id);
	add_2_set(children, power_val->id);
	value_p out = make_value(pow(val->data, power), 0.0, operation, children);
	return out;
}

// divide values
value_p div_value(value_p val1, value_p val2) { // val1 / val2
	return mul_value(val1, pow_value(val2, -1));
}

// negate value
value_p neg_value(value_p val) { // -val
	value_p m_one = make_value(-1.0, 0.0, NULL, NULL);
	return mul_value(val, m_one);
}

// substract values
value_p sub_value(value_p val1, value_p val2) {
	return add_value(val1, neg_value(val2));
}

// perform tanh(value)
value_p tanh_value(value_p val) {
	char* operation = malloc(sizeof(*operation) * 4);
	if(operation == NULL) {
                fprintf(stderr, "Failed to allocate memory for value's operation.");
                exit(EXIT_FAILURE);
        }
	strcpy(operation, "tnh");
	set_p children = make_set_p();
	add_2_set(children, val->id);
	value_p out = make_value((exp(2 * val->data) - 1) / (exp(2 * val->data) + 1), 0.0, operation, children);
	return out;
}

// perform e**value
value_p exp_value(value_p val) {
	char* operation = malloc(sizeof(*operation) * 4);
	if(operation == NULL) {
                fprintf(stderr, "Failed to allocate memory for value's operation.");
                exit(EXIT_FAILURE);
        }
	strcpy(operation, "exp");
	set_p children = make_set_p();
	add_2_set(children, val->id);
	value_p out = make_value((exp(val->data)), 0.0, operation, children);
	return out;
}

// free memory that had been allocated for the value
void free_value(value_p val) {
	if(val != NULL) {
		if(val->children != NULL) {
			free_set(val->children);
		}
		if(val->operation != NULL) {
			free(val->operation);
		}
		free(val);	
	}
}
