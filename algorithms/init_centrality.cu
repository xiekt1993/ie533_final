centrality_device init_centrality(network_in_device nw_host){
  // this is stored at GPU
  const n_nodes num_nodes = *nw_host.csr_info.number_of_nodes;
  const uint8_t n_links = nw_host.csr_info.row_ptr[num_nodes];

  centrality_device c_device;
  centrality_device c_host;

  c_host.centrality = new double[num_nodes];
  c_host.centrality_tree = new double[n_links];
  c_host.message_sent = new double[n_links];
  c_host.inv_position = cal_inv_position(nw_host.csr_info);

  cudaMalloc((void **) &c_device.centrality, num_nodes * sizeof(double));
  cudaMalloc((void **) &c_device.centrality_tree, n_links * sizeof(double));
  cudaMalloc((void **) &c_device.message_sent, n_links * sizeof(double));
  cudaMalloc((void **) &c_device.inv_position, n_links * sizeof(int));

  // initialize
  for(int i = 0; i < num_nodes; i++){
    c_host.centrality[i] = 0;
    if(nw_host.nw_info.nodes_types[i] == NODE_TYPE_STUBBORN_N){
      c_host.centrality_tree[i] = 1;
      c_host.message_sent[i] = 1;
    }else{
      c_host.centrality_tree[i] = 0;
      c_host.message_sent[i] = 0;
    }
  }

  cudaMemcpy(c_device.centrality, c_host.centrality,
    num_nodes * sizeof(double), cudaMemcpyHostToDevice);
  cudaMemcpy(c_device.centrality_tree, c_host.centrality_tree,
    num_links * sizeof(double), cudaMemcpyHostToDevice);
  cudaMemcpy(c_device.message_sent, c_host.message_sent,
    num_links * sizeof(double), cudaMemcpyHostToDevice);
  cudaMemcpy(c_device.inv_position, c_host.inv_position,
    num_links * sizeof(int), cudaMemcpyHostToDevice);

  delete[] c_host.centrality;
  delete[] c_host.centrality_tree;
  delete[] c_host.message_sent;

  return c_device;
}
