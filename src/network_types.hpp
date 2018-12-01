#ifndef NW_TYPES
#define NW_TYPES

using namespace std;

// type for number of nodes and time periods
typedef unsigned int n_nodes;
typedef unsigned short int n_time;

// store the adjacenty list and weighted adjacenty list
// for sparse networks
typedef vector<vector<uint8_t> > adjacency_list;
typedef vector<vector<double> > influence_list;

struct sbm_parameters{
  n_nodes number_of_nodes;
  vector<double> class_probability;
  vector<vector<double> > link_probability_matrix;
};

enum node_type{
  NODE_TYPE_REGULAR,
  NODE_TYPE_STUBBORN_P,
  NODE_TYPE_STUBBORN_N
};

typedef vector<node_type> node_types;

typedef vector<double> r_dirichlet;

struct sparse_csr_weighted{
  n_nodes *number_of_nodes;
  // length = number_of_nodes
  double *confidence;
  // length = non_zero_elems, weights data
  double *influence;
  // same length as influence, corresponding linked nodes
  int *col_index;
  // length = number_of_nodes + 1
  int *row_ptr;
};

struct network_info{
  node_type* nodes_types;
  uint8_t* time_length;
  double* p_threshold;
  double* n_threshold;
};

struct simulation_single{
  double* evidence;
  int* activated_positive;
  int* activated_negative;
  int* total_activated_positive;
  int* total_activated_negative;
};

struct simulation_greedy{
  // equal to the nubmer of regular nodes
  int *total_activated_n;
  int *total_activated_p;
  int *objective;
};

struct network_in_device{
  sparse_csr_weighted csr_info;
  network_info nw_info;
  simulation_single sim_ptr;
};

#endif
