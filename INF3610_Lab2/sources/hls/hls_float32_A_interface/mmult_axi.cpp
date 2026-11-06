#include "mmult_axi.h"
#include "../common/float32/mmult_core.h"
#include <stdint.h>

static mat_type bits_to_float(ap_uint<32> bits) {
 union { uint32_t u; float f; } cvt;
 cvt.u = (uint32_t)bits;
 return cvt.f;
}
static ap_uint<32> float_to_bits(mat_type value) {
 union { uint32_t u; float f; } cvt;
 cvt.f = value;
 return cvt.u;
}

void HLS_accel(hls::stream<AXI_VAL> &INPUT_STREAM,
               hls::stream<AXI_VAL> &OUTPUT_STREAM) {
#pragma HLS INTERFACE axis port=INPUT_STREAM
#pragma HLS INTERFACE axis port=OUTPUT_STREAM
#pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
 mat_type a[DIM][DIM], b[DIM][DIM], c[DIM][DIM];
 // One MM2S transaction: A (row-major) followed by B (row-major).
 // Incoming TLAST is consumed, but not used to terminate the fixed-size transfer.
 for(int i=0;i<DIM;++i)
  for(int j=0;j<DIM;++j) {
#pragma HLS PIPELINE II=1
   AXI_VAL w=INPUT_STREAM.read();
   a[i][j]=bits_to_float(w.data);
  }
 for(int i=0;i<DIM;++i)
  for(int j=0;j<DIM;++j) {
#pragma HLS PIPELINE II=1
   AXI_VAL w=INPUT_STREAM.read();
   b[i][j]=bits_to_float(w.data);
  }
 mmult_core(a,b,c);
 for(int i=0;i<DIM;++i)
  for(int j=0;j<DIM;++j) {
#pragma HLS PIPELINE II=1
   AXI_VAL w;
   w.data=float_to_bits(c[i][j]);
   w.keep=-1; w.strb=-1;
   w.user=0; w.id=0; w.dest=0;
   w.last=(i==DIM-1 && j==DIM-1) ? 1 : 0;
   OUTPUT_STREAM.write(w);
  }
}
