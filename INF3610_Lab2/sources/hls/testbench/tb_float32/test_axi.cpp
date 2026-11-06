#include <stdio.h>
#include <stdint.h>
#include "../../common/float32/mmult_config.h"
#include "../../common/float32/mmult_reference.h"
#include "../../hls_float32_A_interface/mmult_axi.h"
static AXI_VAL make_word(mat_type x, bool last) {
 union { float f; uint32_t u; } cvt; cvt.f=x;
 AXI_VAL w;
 w.data=cvt.u; w.keep=-1; w.strb=-1;
 w.user=0; w.id=0; w.dest=0; w.last=last?1:0;
 return w;
}
static mat_type decode_word(const AXI_VAL &w) {
 union { float f; uint32_t u; } cvt;
 cvt.u=(uint32_t)w.data; return cvt.f;
}
int main() {
 mat_type a[DIM][DIM],b[DIM][DIM],ref[DIM][DIM];
 init_matrices(a,b); mmult_reference(a,b,ref);
 hls::stream<AXI_VAL> in("in"),out("out");
 for(int i=0;i<DIM;++i)for(int j=0;j<DIM;++j)
  in.write(make_word(a[i][j],false));
 for(int i=0;i<DIM;++i)for(int j=0;j<DIM;++j)
  in.write(make_word(b[i][j],i==DIM-1 && j==DIM-1));
 HLS_accel(in,out);
 int errors=0;
 for(int i=0;i<DIM;++i)for(int j=0;j<DIM;++j) {
  if(out.empty()) { printf("Missing output at %d,%d\n",i,j); return 1; }
  AXI_VAL w=out.read();
  if(decode_word(w)!=ref[i][j]) ++errors;
  if((bool)w.last != (i==DIM-1 && j==DIM-1)) ++errors;
  if((unsigned)w.keep != 15U || (unsigned)w.strb != 15U) ++errors;
 }
 if(!out.empty()) ++errors;
 printf("AXIS DIM=%d: %s (%d errors)\n",DIM,errors?"FAIL":"PASS",errors);
 return errors?1:0;
}
