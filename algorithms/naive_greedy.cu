// __host__
#ifndef NAIVE_GREEDY
#define NAIVE_GREEDY

using namespace std;

__global__
void cal_obj(simulation_greedy sim_greedy, network_in_device nw_device){
  int new_exp_id = threadIdx.x;
  int num_nodes = *nw_device.csr_info.number_of_nodes;

  if(
    (new_exp_id >= num_nodes)
    ||
    (nw_device.nw_info.nodes_types[new_exp_id] != NODE_TYPE_REGULAR)
  ) return;

  for(int i = 0; i < num_nodes; i++){
    sim_greedy.objective[new_exp_id] +=
      (sim_greedy.total_activated_p[new_exp_id * num_nodes + i]
      - sim_greedy.total_activated_n[new_exp_id * num_nodes + i]);
  }
}

// host : give the best next node
int naive_greedy(network_in_device nw_host, network_in_device nw_device){
  int best_node;
  int max_obj = 0;
  const int& num_nodes = *nw_host.csr_info.number_of_nodes;

  simulation_greedy sim_greedy = init_greedy(nw_host);
  int *objective = new int[num_nodes];
  cudaFree(nw_device.sim_ptr.total_activated_positive);
  cudaFree(nw_device.sim_ptr.total_activated_negative);

  // loop to get results
  for(int node =  0; node < num_nodes; node ++){
    if(nw_host.csr_info.nodes_types[node] != NODE_TYPE_REGULAR){
      max_obj--;
      continue;
    }
    cudaMemset((nw_device.nw_info.nodes_types + node), NODE_TYPE_STUBBORN_P, sizeof(node_type));
    nw_device.sim_ptr.total_activated_positive = sim_greedy.total_activated_p + num_nodes * node;
    nw_device.sim_ptr.total_activated_negative = sim_greedy.total_activated_n + num_nodes * node;
    for(int t = 0){
      device_cal_evidence_global<<<1, 1024>>>(nw_device, t);
      cudaDeviceSynchronize();
    }
    cudaMemset((nw_device.nw_info.nodes_types + node), NODE_TYPE_REGULAR, sizeof(node_type));
  }

  // calculate the final results
  cal_obj<<<1, 1024>>>(sim_greedy, nw_device);
  // copy result back
  cudaMemcpy(objective, sim_greedy.objective, num_nodes * sizeof(int), cudaMemcpyDeviceToHost);
  // find optimal node and return
  for(int node = 0; node < num_nodes; node ++){
    if(max_obj < objective[node]){
      best_node = node;
      max_obj = objective[node];
    }
  }
  return best_node;
}

#endif
