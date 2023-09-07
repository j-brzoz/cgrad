#ifndef LOSS_H
#define LOSS_H

#include "./data_structs/value.h"
#include <stdio.h>

// loss function: mean square error
value_p mean_sqr_error(value_p* pred, value_p* actual, size_t num);

#endif
