#include "array.h"
#include "../ml_structs/value.h"
#include <stdio.h>
#include <stdlib.h>

// make array of values
val_array_p make_val_array() {
	val_array_p a = malloc(sizeof(*a));
	if (a == NULL) {
        fprintf(stderr, "Failed to initialize global value array.\n");
        return NULL;
    }
	a->size = 2;
	a->num_of_elements = 0;
	a->elements = malloc(sizeof(value_p) * a->size);
	if (a->elements == NULL) {
		fprintf(stderr, "Failed to allocate memory for global value array elements.\n");
		free(a);  
		return NULL;
    }
	return a;
}

// add value to the array of values
void add_2_val_array(val_array_p a, const value_p val) {
	if (a->size == a->num_of_elements) {
		increase_val_array(a);
	}
	a->elements[a->num_of_elements] = val;
	a->num_of_elements++;
}

void increase_val_array(val_array_p a) {
	a->size *= 2;
    value_p* new_array = realloc(a->elements, sizeof(value_p) * a->size);
    if (new_array == NULL) {
        fprintf(stderr, "Failed to reallocate memory for increased val_array.\n");
        exit(EXIT_FAILURE);
    }
    a->elements = new_array;
}

// free memory that had been allocated for the array of values
void free_val_array(val_array_p a) {
	if(a != NULL) {
		if(a->elements != NULL) {
			for(size_t i = 0; i < a->num_of_elements; i++) {
				free_value(a->elements[i]);
			}
			free(a->elements);
		}
		free(a);
	}
}
