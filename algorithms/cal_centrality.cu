// this is based on Prof. Ozdaglar's work
// returns HIC
__global__
int cal_centrality(network_in_device nw_device, centrality_device c_device){
  int node_id = threadIdx.x;

  // update centrality tree

  // update message sent
}
