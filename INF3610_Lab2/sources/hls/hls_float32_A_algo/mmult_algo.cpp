#include "mmult_algo.h"
#include "../common/float32/mmult_core.h"
void mmult_hw(mat_type a[DIM][DIM], mat_type b[DIM][DIM], mat_type c[DIM][DIM]) {
 mmult_core(a,b,c);
}
