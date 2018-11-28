/*
struct sparse_csr_weighted{
  n_nodes *number_of_nodes;
  double *confidence;
  double *influence;
  int *col_index;
  int *row_ptr;
};
*/

// __host__
network_in_device cp_to_device(const sparse_csr_weighted &csr_info, const network_info &h_nw_info){
  network_in_device nw_device;
  sparse_csr_weighted& device_initial_info = nw_device.csr_info;
  network_info& nw_info = nw_device.nw_info;
  simulation_single& sim_ptr = nw_device.sim_ptr;

  const n_nodes num_nodes = *csr_info.number_of_nodes;
  const uint8_t n_links = csr_info.row_ptr[num_nodes];
  const uint8_t& t_length = *h_nw_info.time_length;

  cudaMalloc((void**) &(device_initial_info.number_of_nodes), sizeof(n_nodes));
  cudaMemcpy(device_initial_info.number_of_nodes, csr_info.number_of_nodes, sizeof(n_nodes), cudaMemcpyHostToDevice);
  cudaMalloc((void**) &(device_initial_info.confidence),
    num_nodes * sizeof(double));
  cudaMemcpy(device_initial_info.confidence, csr_info.confidence,
    num_nodes * sizeof(double), cudaMemcpyHostToDevice);
  cudaMalloc((void**) &(device_initial_info.influence),
    n_links * sizeof(double));
  cudaMemcpy(device_initial_info.influence, csr_info.influence,
    n_links * sizeof(double), cudaMemcpyHostToDevice);
  cudaMalloc((void**) &(device_initial_info.col_index),
    n_links * sizeof(int));
  cudaMemcpy(device_initial_info.col_index, csr_info.col_index,
    n_links * sizeof(int), cudaMemcpyHostToDevice);
  cudaMalloc((void**) &(device_initial_info.row_ptr),
    (num_nodes + 1) * sizeof(int));
  cudaMemcpy(device_initial_info.row_ptr, csr_info.row_ptr,
    (num_nodes + 1) * sizeof(int), cudaMemcpyHostToDevice);

  cudaMalloc((void**) &(nw_info.nodes_types), num_nodes * sizeof(node_type));
  cudaMemcpy(nw_info.nodes_types, h_nw_info.nodes_types,
    num_nodes * sizeof(node_type), cudaMemcpyHostToDevice);
  cudaMalloc((void**) &(nw_info.time_length), sizeof(uint8_t));
  cudaMemcpy(nw_info.time_length, &t_length, sizeof(uint8_t), cudaMemcpyHostToDevice);
  cudaMalloc((void**) &(nw_info.p_threshold), sizeof(double));
  cudaMemcpy(nw_info.p_threshold, h_nw_info.p_threshold, sizeof(double), cudaMemcpyHostToDevice);
  cudaMalloc((void**) &(nw_info.n_threshold), sizeof(double));
  cudaMemcpy(nw_info.n_threshold, h_nw_info.n_threshold, sizeof(double), cudaMemcpyHostToDevice);

  // accrued evidence is num_nodes * time_length
  cudaMalloc((void**) &(sim_ptr.evidence), num_nodes * t_length * sizeof(double));
  // think i'd rather use local memory
  cudaMalloc((void**) &(sim_ptr.activated_positive), num_nodes * t_length * sizeof(int));
  cudaMalloc((void**) &(sim_ptr.activated_negative), num_nodes * t_length * sizeof(int));
  cudaMalloc((void**) &(sim_ptr.total_activated_positive), num_nodes * sizeof(int));
  cudaMalloc((void**) &(sim_ptr.total_activated_negative), num_nodes * sizeof(int));

  return nw_device;
}

void clean_device_memory(network_in_device &nw_device){
  sparse_csr_weighted& device_initial_info = nw_device.csr_info;
  network_info& nw_info = nw_device.nw_info;
  simulation_single& sim_ptr = nw_device.sim_ptr;

  cudaFree(device_initial_info.number_of_nodes);
  cudaFree(device_initial_info.confidence);
  cudaFree(device_initial_info.influence);
  cudaFree(device_initial_info.col_index);
  cudaFree(device_initial_info.row_ptr);

  cudaFree(nw_info.nodes_types);
  cudaFree(nw_info.time_length);
  cudaFree(nw_info.p_threshold);
  cudaFree(nw_info.n_threshold);

  cudaFree(sim_ptr.evidence);
  cudaFree(sim_ptr.activated_positive);
  cudaFree(sim_ptr.activated_negative);

  return;
}
