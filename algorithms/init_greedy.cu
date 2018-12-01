#ifndef INIT_GREEDY
#define INIT_GREEDY

simulation_greedy init_greedy(const network_in_device& nw_host){
  simulation_greedy sim_greedy;

  const int& num_nodes = *nw_host.csr_info.number_of_nodes;

  cudaMalloc((void **) &sim_greedy.total_activated_p, num_nodes * num_nodes * sizeof(int));
  cudaMalloc((void **) &sim_greedy.total_activated_n, num_nodes * num_nodes * sizeof(int));
  cudaMalloc((void **) &sim_greedy.objective, num_nodes * sizeof(int));

  return sim_greedy;
}

#endif
