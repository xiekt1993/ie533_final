#ifndef CUDAINCLUDE
#define CUDAINCLUDE

#include <stdint.h>

#include<iostream>
#include<list>
#include<vector>
#include<fstream>
#include<string>

#include "network_types.hpp"

#include "./utils/save_read_network.hpp"
#include "./utils/cp_to_device.cu"

#include "./device_utils/copy_to_host.cu"
#include "./device_utils/device_cal_influence.cu"

#endif
