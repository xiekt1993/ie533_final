using namespace std;

sparse_csr_weighted init_mcmc(network_in_device& nw_host){
  // only need confidence and influence
  sparse_csr_weighted proposal_csr;

  const int& num_nodes = *nw_host.csr_info.number_of_nodes;
  const int& num_links = nw_host.csr_info.row_ptr[num_nodes];

  proposal_csr.confidence = new double[num_nodes];
  proposal_csr.influence = new double[num_links];

  return proposal_csr;
}
