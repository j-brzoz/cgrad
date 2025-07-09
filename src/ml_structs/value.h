#ifndef VALUE_H
#define VALUE_H

#include "../data_structs/set.h"
#include "../data_structs/array.h"
#include <stdio.h>

typedef struct value {
	size_t id;	  // unique id
	double data;      // data 
	double gradient;  // gradient
	set_p children;   // ids of values that made that value; if new value, children is null 
	char* operation;  // which operation made that value; if new value, operation is null
} value_t, *value_p;

extern size_t* id;
extern val_array_p global_array;

// initializes the global value system
int value_system_init();
// clean up the global value system
void value_system_cleanup();
// make a value
value_p make_value(double data, double gradient, const char* operation, set_p children);
// print value's data
void print_value(const value_p val);
// add two values
value_p add_value(const value_p val1, const value_p val2);
// multiply two values
value_p mul_value(const value_p val1, const value_p val2);
// raise value to the power
value_p pow_value(const value_p val, double power);
// divide values
value_p div_value(const value_p val1, const value_p val2);
// nagate value
value_p neg_value(const value_p val);
// substract values
value_p sub_value(const value_p val1, const value_p val2);
// perform tanh(value)
value_p tanh_value(const value_p val);
// perform e**value
value_p exp_value(const value_p val);
// free memory that had been allocated for the value
void free_value(value_p val);

#endif
