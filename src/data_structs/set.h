#ifndef SET_H
#define SET_H

#include <stdio.h>

typedef struct set {
	size_t* elements;       // elements
	size_t size;            // memory allocated for elements
	size_t num_of_elements; // actual number of elements
} set_t, *set_p;

// make a set
set_p make_set_p();
// add an element to the set
size_t add_2_set(set_p s, const size_t val);
// check if element is already in the set 
size_t check_if_in_set(const set_p s, const size_t val);
// double the size of set
void increase_set(set_p s);
// free memory that had been allocated for the set
void free_set(const set_p s);

#endif
