double cal_llh(const sparse_csr_weighted& proposal_csr, const network_in_device& nw_host,
  const n_nodes& proposal_node){

  double llh = 0;
  const n_nodes& num_nodes = *nw_host.csr_info.number_of_nodes;
  const uint8_t& t_length = *nw_host.nw_info.time_length;

  // borrow the memory in nw_host
  for(int t = 0; t < t_length; t++){
    for(int node = 0; node < num_nodes; node++){
      if(t == 0){
        // assume initialized
        continue;
      }
      // node's type preassumed regular
      // otherwise no need to update
      const int& linked_node_start = nw_host.csr_info.row_ptr[node];
      const int& linked_node_end = nw_host.csr_info.row_ptr[node + 1];

      double& current_evidence = nw_host.sim_ptr.evidence[num_nodes * t + node];
      double& prev_evidence = nw_host.sim_ptr.evidence[num_nodes * (t - 1) + node];
      int node_status = nw_host.sim_ptr.activated_positive[num_nodes * t + node]
        - nw_host.sim_ptr.activated_negative[num_nodes * t + node];

      if(node == proposal_node){
        current_evidence = prev_evidence * proposal_csr.confidence[node];
        for(int node2 = linked_node_start; node2 < linked_node_end; node2++){
          const int& node2_index = nw_host.csr_info.col_index[node2];
          current_evidence += nw_host.sim_ptr.evidence[num_nodes * (t - 1) + node2_index]
            * proposal_csr.influence[node2];
        }
        llh += ;
      }else{
        current_evidence = prev_evidence * nw_info.csr_info.confidence[node];
        for(int node2 = linked_node_start; node2 < linked_node_end; node2++){
          const int& node2_index = nw_host.csr_info.col_index[node2];
          current_evidence += nw_host.sim_ptr.evidence[num_nodes * (t - 1) + node2_index]
            * nw_info.csr_info.influence[node2];
        }
        llh += ;
      }
    }
  }

  return llh;
}
