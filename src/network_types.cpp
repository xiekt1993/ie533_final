using namespace std;

// type for number of nodes and time periods
typedef unsigned int n_nodes;
typedef unsigned short int n_time;

// store the adjacenty list and weighted adjacenty list
// for sparse networks
typedef vector<vector<uint8_t>> adjacency_list;
typedef vector<vector<double>> influnce_list;

struct sbm_parameters{
  n_nodes number_of_nodes;
  vector<double> class_probability;
  vector<vector<double>> link_probability_matrix;
};

enum node_type{
  NODE_TYPE_REGULAR,
  NODE_TYPE_STUBBORN_P,
  NODE_TYPE_STUBBORN_N
};

typedef vector<node_type> node_types;

typedef vector<double> r_dirichlet;

struct sparse_csr_weighted{
  n_nodes number_of_nodes;
  // length = number_of_nodes
  double *confidence;
  // length = non_zero_elems
  double *influence;
  // same length as influence
  int *col_index;
  // length = number_of_nodes + 1
  int *row_ptr;
};
