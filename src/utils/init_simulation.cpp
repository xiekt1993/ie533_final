simulation_single *init_simulation(const sparse_csr_weighted &csr_info, const network_info& nw_info){
  simulation_single sim_ptr;

  const n_nodes& num_nodes = *csr_info.number_of_nodes;
  const uint8_t& t_length = *nw_info.time_length;
  sim_ptr.evidence = new double[num_nodes * t_length];
  sim_ptr.activated_positive = new int[num_nodes * t_length];
  sim_ptr.activated_negative = new int[num_nodes * t_length];

  return sim_ptr;
}
