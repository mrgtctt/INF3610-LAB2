#include <stdio.h>
#include "../../common/float32/mmult_config.h"
#include "../../common/float32/mmult_reference.h"
#include "../../hls_float32_A_algo/mmult_algo.h"
int main() {
 mat_type a[DIM][DIM],b[DIM][DIM],ref[DIM][DIM],out[DIM][DIM];
 init_matrices(a,b);
 mmult_hw(a,b,out);
 mmult_reference(a,b,ref);
 int errors=0;
 for(int i=0;i<DIM;++i)for(int j=0;j<DIM;++j)
  if(ref[i][j]!=out[i][j]) ++errors;
 printf("ALGO DIM=%d: %s (%d errors)\n",DIM,errors?"FAIL":"PASS",errors);
 return errors?1:0;
}
