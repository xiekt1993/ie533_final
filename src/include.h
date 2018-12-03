#ifndef INCLUDE
#define INCLUDE

#include<iostream>
#include<list>
#include<vector>
#include<random>
#include<fstream>
#include<stdint.h>

#include "network_types.hpp"

#include "./utils/random_generate.hpp"
#include "./utils/generate_network.hpp"
#include "./utils/to_sparse.hpp"
#include "./utils/gen_sbm_pars.hpp"
#include "./utils/init_simulation.hpp"
#include "./utils/save_read_network.hpp"
// #include "./utils/cal_inv_position.cpp"

#include "./utils/random_proposal.cpp"
#include "./utils/cal_llh.cpp"

#include "../algorithms/init_mcmc.cpp"
#include "../algorithms/mcmc_influence.cpp"
#include "./utils/gen_influence.cpp"

#endif
