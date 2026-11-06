#ifndef MMULT_ALGO_H
#define MMULT_ALGO_H
#include "../common/float32/mmult_config.h"
void mmult_hw(mat_type a[DIM][DIM], mat_type b[DIM][DIM], mat_type c[DIM][DIM]);
#endif
