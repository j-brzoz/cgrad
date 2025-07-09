#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

struct value;
typedef struct value* value_p;

typedef struct val_array {
	value_p* elements;      // elements in array
	size_t size;            // size allocated for the arrey
	size_t num_of_elements; // actual number of elements in the array
} val_array_t, *val_array_p;

// make array of values
val_array_p make_val_array();
// add value to the array of values
void add_2_val_array(val_array_p a, const value_p val);
// increase the size of the array of values
void increase_val_array(val_array_p a);
// free memory that had been allocated for the array of values
void free_val_array(val_array_p a);

#endif
