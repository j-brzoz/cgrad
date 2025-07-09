#include "set.h"
#include <stdio.h>
#include <stdlib.h>

// make a set
set_p make_set_p() {
	set_p s = malloc(sizeof(*s));
	if (s == NULL) {
        	fprintf(stderr, "Failed to allocate memory for set.");
        	exit(EXIT_FAILURE);
    	}
	s->size = 2;
	s->num_of_elements = 0;
	s->elements = malloc(sizeof(size_t) * s->size);
	if (s->elements == NULL) {
        	fprintf(stderr, "Failed to allocate memory for set elements.");
        	free(s);  
		exit(EXIT_FAILURE);
    	}
	return s;
}

// add an element to the set
size_t add_2_set(set_p s, const size_t val) {
	if(check_if_in_set(s, val) == 1) {
		return 0;
	} else {
		if (s->size == s->num_of_elements) {
			increase_set(s);
		}
		s->elements[s->num_of_elements] = val;
		s->num_of_elements++;
		return 1;
	}
}

// check if element is already in the set
size_t check_if_in_set(const set_p s, const size_t val) {
	for(size_t i = 0; i < s->num_of_elements; i++) {
		if(s->elements[i] == val) {
			return 1;
		}
	}
	return 0;
}

// double the size of set
void increase_set(set_p s) {
	s->size *= 2;
	size_t* new_set = malloc(sizeof(size_t) * s->size);
	if (new_set == NULL) {
        	fprintf(stderr, "Failed to allocate memory for increased set.");
        	exit(EXIT_FAILURE);
    	}
	for(size_t i = 0; i < s->num_of_elements; i++) {
		new_set[i] = s->elements[i];
	}
	free(s->elements);
	s->elements = new_set;	
}

// free memory that had been allocated for the set
void free_set(const set_p s) {
	if(s != NULL) {
		if(s->elements != NULL) { 
			free(s->elements);
		}
		free(s);
	}
}
