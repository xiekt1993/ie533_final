int gen_status(double& evidence){
  double prob_p = evidence > 0 ? 1./(1. - evidence) : 0;
  double prob_n = evidence < 0 ? (1./(evidence + 1.)) : 0;
  double prob_r = evidence > 0 ? (1./evidence) : (-1./evidence) ;
  double normalizer = prob_n + prob_p + prob_r;
  prob_p /= normalizer;
  prob_n /= normalizer;
  prob_r /= normalizer;

  double ru = random_uniform();
  if(ru < prob_r) return 0;
  if(ru < prob_r + prob_n) return -1;
  return 1;
}

void generate_influence(network_in_device& nw_host, const double& p_positive){
  const n_nodes num_nodes = *nw_host.csr_info.number_of_nodes;
  const uint8_t t_length = *nw_host.nw_info.time_length;

  for(int i = 0; i < num_nodes; i++){
    if(random_bernoulli(p_positive)) nw_host.nw_info.nodes_types[i] = NODE_TYPE_STUBBORN_P;
  }

  nw_host.sim_ptr.evidence = new double[num_nodes * t_length];
  nw_host.sim_ptr.activated_positive = new int[num_nodes * t_length];
  nw_host.sim_ptr.activated_negative = new int[num_nodes * t_length];

  for(int t = 0; t < t_length; t++){
    for(int node = 0; node < num_nodes; node++){

      double& current_evidence = nw_host.sim_ptr.evidence[t * num_nodes + node];

      if(t == 0){
        switch(nw_host.nw_info.nodes_types[node]){
          case NODE_TYPE_REGULAR:
          nw_host.sim_ptr.evidence[node] = 0;
          break;
          case NODE_TYPE_STUBBORN_N:
          nw_host.sim_ptr.evidence[node] = -1;
          break;
          case NODE_TYPE_STUBBORN_P:
          nw_host.sim_ptr.evidence[node] = 1;
          break;
        }
        continue;

      }else{
        double& prev_evidence = nw_host.sim_ptr.evidence[(t - 1) * num_nodes + node];
        if(nw_host.nw_info.nodes_types[node] != NODE_TYPE_REGULAR){
          current_evidence = prev_evidence;
          // suppose we do not care about its status
          continue;
        }else{
          int& node2_start = nw_host.csr_info.row_ptr[node];
          int& node2_end = nw_host.csr_info.row_ptr[node + 1];

          for(int node2 = node2_start; node2 < node2_end; node2++){
            int& node2_index = nw_host.csr_info.col_index[node2];
            current_evidence += nw_host.sim_ptr.evidence[num_nodes * (t - 1) + node2_index]
              * nw_host.csr_info.influence[node2];
          }

          int status = gen_status(current_evidence);
          if(status == -1)
            nw_host.sim_ptr.activated_negative[num_nodes * t + node] = 1;
          else if(status == 1)
            nw_host.sim_ptr.activated_positive[num_nodes * t + node] = 1;
        }
      }


    }
  }

  return;
}
