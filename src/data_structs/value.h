#ifndef VALUE_H
#define VALUE_H

#include "set.h"
#include <stdio.h>

typedef struct value {
	size_t id;	  // unique id
	double data;      // data 
	double gradient;  // gradient
	set_p children;   // ids of values that made that value; if new value, children is null 
	char* operation;  // which operation made that value; if new value, operation is null
} value_t, *value_p;

// make a value
value_p make_value(double data, double gradient, char* operation, set_p children);
// print value's data
void print_value(value_p val);
// add two values
value_p add_value(value_p val1, value_p val2);
// multiply two values
value_p mul_value(value_p val1, value_p val2);
// raise value to the power
value_p pow_value(value_p val, double power);
// divide values
value_p div_value(value_p val1, value_p val2);
// nagate value
value_p neg_value(value_p val);
// substract values
value_p sub_value(value_p val1, value_p val2);
// perform tanh(value)
value_p tanh_value(value_p val);
// perform e**value
value_p exp_value(value_p val);
// free memory that had been allocated for the value
void free_value(value_p val);

#endif
