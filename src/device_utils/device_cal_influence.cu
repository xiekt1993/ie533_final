// device utility to calculate target evidence
__device__
void device_cal_evidence(network_in_device &nw_device, const int &node_id, const int &t){
  sparse_csr_weighted& csr_info = nw_device.csr_info;
  network_info& nw_info = nw_device.nw_info;
  simulation_single& sim_ptr = nw_device.sim_ptr;

  const n_nodes num_nodes = *csr_info.number_of_nodes;
  const double& confidence = csr_info.confidence[node_id];
  const double& p_threashold = *nw_info.p_threshold;
  const double& n_threashold = *nw_info.n_threshold;

  double *current_evidence = sim_ptr.evidence + t * num_nodes + node_id;

  int *p_activated = sim_ptr.activated_positive + t * num_nodes + node_id;
  int *n_activated = sim_ptr.activated_negative + t * num_nodes + node_id;

  int *total_activated_p = sim_ptr.total_activated_positive + node_id;
  int *total_activated_n = sim_ptr.total_activated_negative + node_id;

  if(t == 0){
    if(nw_info.nodes_types[node_id] == NODE_TYPE_STUBBORN_P){
      *current_evidence = 1;
      *p_activated = 1;
      *n_activated = 0;
      *total_activated_p ++;
    }

    else if(nw_info.nodes_types[node_id] == NODE_TYPE_STUBBORN_N){
      *current_evidence = -1;
      *p_activated = 0;
      *n_activated = 1;
      *total_activated_n ++;
    }

    else{
      *current_evidence = 0;
      *p_activated = 0;
      *n_activated = 0;
    }
    return;
  }

  double *prev_evidence = sim_ptr.evidence + (t - 1) * num_nodes + node_id;

  if(nw_info.nodes_types[node_id] != NODE_TYPE_REGULAR){
    *current_evidence = *prev_evidence;
    return;
  }

  (*current_evidence) = (*prev_evidence) * confidence;

  const int n_linked_nodes = csr_info.row_ptr[node_id + 1] - csr_info.row_ptr[node_id];
  int node_ind;
  for(int node = 0; node < n_linked_nodes; node++){
    node_ind = csr_info.col_index[csr_info.row_ptr[node_id] + node];

    if(
      *(sim_ptr.activated_positive + (t - 1) * num_nodes + node_ind)
      ||
      *(sim_ptr.activated_negative + (t - 1) * num_nodes + node_ind)
    ) // only activated nodes can send evidence
    *current_evidence +=
      csr_info.influence[csr_info.row_ptr[node_id] + node]
      *
      *(sim_ptr.evidence + (t - 1) * num_nodes + node_ind)
      ;
  }

  if(*evidence > p_threshold){
    *p_activated = 1;
    *n_activated = 0;
    *total_activated_p ++;
  }
  else if(*evidence < n_threshold){
    *p_activated = 0;
    *n_activated = 1;
    *total_activated_n ++;
  }else{
    *p_activated = 0;
    *n_activated = 0;
  }

  return;
}

__global__
void device_cal_evidence_global(network_in_device &nw_device, const int& t){
  // less than 1024 nodes case
  const n_nodes num_nodes = *nw_device.csr_info.number_of_nodes;
  int t_id = threadIdx.x;
  if(t_id < num_nodes)  device_cal_evidence(nw_device, t_id, t);
  // maybe i dont need this
  // __syncthreads();
  return;
}

/*
__global__
void device_cal_evidence_global_large(network_in_device &nw_device, const int& t){
  int t_id = threadIdx.x;

  return;
}
*/

int device_cal_evidence_host(const sparse_csr_weighted &csr_info, const network_info &h_nw_info){
  // we need number of threads equal to the nmber of nodes
  network_in_device nw_device = cp_to_device(csr_info, h_nw_info);

  const n_nodes num_nodes = *(csr_info.number_of_nodes);
  const int t_length = *h_nw_info.time_length;
  const int n_threads = 1024;
  for(int t = 0; t < t_length; t++){
    // for less than 1024 nodes
    device_cal_evidence_global<<<1, n_threads>>>(nw_device, t);
  }

  int *sim_activated_positive = new int[num_nodes];
  int *sim_activated_negative = new int[num_nodes];
  // copy results back to ram
  cudaMemcpy(nw_device.sim_ptr.total_activated_positive, sim_activated_positive,
    num_nodes * sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(nw_device.sim_ptr.total_activated_negative, sim_activated_negative,
    num_nodes * sizeof(int), cudaMemcpyDeviceToHost);

  int obj = 0;
  for(int n = 0; n < num_nodes; n++){
    obj += sim_activated_positive[n] - sim_activated_negative[n];
  }
  clean_device_memory(nw_device);

  return obj;
}
