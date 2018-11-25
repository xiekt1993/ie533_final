network_info init_info(const sparse_csr_weighted &csr_info, const double& p_negative,
  const uint8_t& t_length, const double& abs_threshold){
  network_info nw_info;  

  const n_nodes& num_nodes = *csr_info.number_of_nodes;

  nw_info.nodes_types = new node_type[num_nodes];
  for(int i = 0; i < num_nodes; i++){
    if(random_bernoulli(p_negative)) nw_info.nodes_types[i] = NODE_TYPE_STUBBORN_N;
    else nw_info.nodes_types[i] = NODE_TYPE_REGULAR;
  }
  nw_info.time_length = new uint8_t();
  *nw_info.time_length = t_length;
  nw_info.p_threshold = new double();
  nw_info.n_threshold = new double();
  *nw_info.p_threshold = abs_threshold;
  *nw_info.n_threshold = -abs_threshold;

  return nw_info;
}

network_in_device init_simulation(const sparse_csr_weighted &csr_info, const network_info &nw_info){
  network_in_device nw_host;
  simulation_single sim_ptr;

  const n_nodes& num_nodes = *csr_info.number_of_nodes;
  const uint8_t& t_length = *nw_info.time_length;

  sim_ptr.evidence = new double[num_nodes * t_length];
  sim_ptr.activated_positive = new int[num_nodes * t_length];
  sim_ptr.activated_negative = new int[num_nodes * t_length];

  nw_host.csr_info = csr_info;
  nw_host.nw_info = nw_info;
  nw_host.sim_ptr = sim_ptr;

  return nw_host;
}
