#ifndef MMULT_CONFIG_H
#define MMULT_CONFIG_H
// Same configuration for both HLS components. Start with 4, then try 42.
#ifndef MMULT_DIM
#define MMULT_DIM 42
#endif
static const int DIM = MMULT_DIM;
static const int SIZE = DIM * DIM;
typedef float mat_type;
#endif
