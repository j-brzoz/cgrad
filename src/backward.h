#ifndef BACKWARD_H 
#define BACKWARD_H

#include "./data_structs/set.h"
#include "./ml_structs/value.h"
#include <stdio.h>

// sorts all values in reverse topological order for backward pass
void reverse_topological_sort(const value_p node, set_p visited, set_p rev_topo_ord);
// derivative for addition
void backward_add(const value_p val);
// derivative for multiplication
void backward_mul(const value_p val);
// derivative for pow operation
void backward_pow(const value_p val);
// derivative for tanh operation
void backward_tanh(const value_p val);
// derivative for exp operation
void backward_exp(const value_p val);
// backward pass through all children values
void backward(value_p val);

#endif
