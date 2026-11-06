#ifndef MMULT_AXI_H
#define MMULT_AXI_H
#include "../common/float32/mmult_config.h"
#include <ap_axi_sdata.h>
#include <hls_stream.h>
// Retain original 32-bit AXIS payload and sideband widths.
typedef ap_axiu<32,4,5,5> AXI_VAL;
void HLS_accel(hls::stream<AXI_VAL> &INPUT_STREAM,
               hls::stream<AXI_VAL> &OUTPUT_STREAM);
#endif
