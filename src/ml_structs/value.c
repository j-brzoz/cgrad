#include "value.h"
#include "../data_structs/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

size_t* id = NULL;
val_array_p global_array = NULL;

int value_system_init() {
    if (id != NULL || global_array != NULL) {
        fprintf(stderr, "Value system already initialized.\n");
        return 0;
    }

    id = malloc(sizeof(size_t));
    if (id == NULL) {
        fprintf(stderr, "Failed to allocate memory for global ID counter.\n");
        return -1;
    }
    *id = 0;

    global_array = make_val_array();
    if (global_array == NULL) {
        free(id);
        id = NULL;
        return -1;
    }
    return 0;
}

void value_system_cleanup() {
    if (id != NULL) {
        free(id);
        id = NULL;
    }
    if (global_array != NULL) {
        free_val_array(global_array);
        global_array = NULL;
    }
}

// make a value
value_p make_value(double data, double gradient, const char* operation, set_p children) {
    if (id == NULL || global_array == NULL) {
        fprintf(stderr, "Error: Value system not initialized. Call value_system_init() first.\n");
        return NULL;
    }
	value_p out = malloc(sizeof(*out));
	if(out == NULL) {
        fprintf(stderr, "Failed to allocate memory for value_t object.\n");
        return NULL;
    }

	out->id = *id;
    *id += 1;

	out->data = data;
	out->gradient = gradient;

	out->operation = (operation != NULL) ? strdup(operation) : NULL;
	if (operation != NULL && out->operation == NULL) {
        fprintf(stderr, "Failed to duplicate operation string.\n");
        free(out);
        return NULL;
    }
	out->children = children;
	add_2_val_array(global_array, out);
	return out;
}

// print value's data
void print_value(const value_p val) {
	printf("Value(data=%f)\n", val->data);
}

// add two values
value_p add_value(const value_p val1, const value_p val2) {
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
	free(operation);
	return out;
}

// multiply two values
value_p mul_value(const value_p val1, const value_p val2) {
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
	free(operation);
	return out;
}

// raise value to the power
value_p pow_value(const value_p val, double power) { // only supports float powers
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
	free(operation);
	return out;
}

// divide values
value_p div_value(const value_p val1, const value_p val2) { // val1 / val2
	return mul_value(val1, pow_value(val2, -1));
}

// negate value
value_p neg_value(const value_p val) { // -val
	value_p m_one = make_value(-1.0, 0.0, NULL, NULL);
	return mul_value(val, m_one);
}

// substract values
value_p sub_value(const value_p val1, const value_p val2) {
	return add_value(val1, neg_value(val2));
}

// perform tanh(value)
value_p tanh_value(const value_p val) {
	char* operation = malloc(sizeof(*operation) * 4);
	if(operation == NULL) {
                fprintf(stderr, "Failed to allocate memory for value's operation.");
                exit(EXIT_FAILURE);
        }
	strcpy(operation, "tnh");
	set_p children = make_set_p();
	add_2_set(children, val->id);
	value_p out = make_value((exp(2 * val->data) - 1) / (exp(2 * val->data) + 1), 0.0, operation, children);
	free(operation);
	return out;
}

// perform e**value
value_p exp_value(const value_p val) {
	char* operation = malloc(sizeof(*operation) * 4);
	if(operation == NULL) {
                fprintf(stderr, "Failed to allocate memory for value's operation.");
                exit(EXIT_FAILURE);
        }
	strcpy(operation, "exp");
	set_p children = make_set_p();
	add_2_set(children, val->id);
	value_p out = make_value((exp(val->data)), 0.0, operation, children);
	free(operation);
	return out;
}

// free memory that had been allocated for the value
void free_value(const value_p val) {
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
