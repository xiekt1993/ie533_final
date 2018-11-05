#ifndef INCLUDE
#define INCLUDE

#include<iostream>
#include<list>
#include<vector>
#include<random>

// #include<cuda_runtime.h>
// #include "cublas_v2.h"

#include "network_types.cpp"

#include "./utils/random_generate.cpp"
#include "./utils/generate_network.cpp"
#include "./utils/to_sparse.cpp"

#include "./utils/cp_to_device.cu"

#endif
