#include "./ml_structs/value.h"
#include <stdio.h>

// loss function: mean square error
value_p mean_sqr_error(value_p* pred, value_p* actual, size_t num) {
	value_p loss = make_value(0.0, 0.0, NULL, NULL);
	for(size_t i = 0; i < num; i++) {
		loss = add_value(loss, pow_value(sub_value(pred[i], actual[i]), 2));
	}
	return loss;
}	
