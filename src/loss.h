#ifndef LOSS_H
#define LOSS_H

#include "./ml_structs/value.h"
#include <stdio.h>

// loss function: mean square error
value_p mean_sqr_error(const value_p* pred, const value_p* actual, const size_t num);

#endif
