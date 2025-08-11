#include "./ml_structs/value.h"
#include <stdio.h>

// loss function: mean square error
value_p mean_sqr_error(const value_p* pred, const value_p* actual, const size_t num) {
	value_p loss = make_value(0.0, 0.0, NULL, NULL);
	for(size_t i = 0; i < num; i++) {
		loss = add_value(loss, pow_value(sub_value(pred[i], actual[i]), 2));
	}
	value_p batch_size = make_value(num, 0.0, NULL, NULL);
	loss = div_value(loss, batch_size);
	return loss;
}	
