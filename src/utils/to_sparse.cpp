// convert the adjacency list to
// sparse representation that can be
// understood by gpu

sparse_csr_weighted to_sparse(const adjacency_list& adj_list, const influence_list& influence){
  sparse_csr_weighted csr_info;

  csr_info.number_of_nodes = new n_nodes();
  *(csr_info.number_of_nodes) = adj_list.size();
  csr_info.confidence = new double[*csr_info.number_of_nodes];
  csr_info.row_ptr = new int[*csr_info.number_of_nodes + 1]();

  for(int i = 0; i < *csr_info.number_of_nodes; i++){
    csr_info.row_ptr[i + 1] = csr_info.row_ptr[i] + adj_list[i].size();
    csr_info.confidence[i] = influence[i].back();
  }

  const int &n_data = csr_info.row_ptr[*csr_info.number_of_nodes];
  csr_info.influence = new double[n_data];
  csr_info.col_index = new int[n_data];
  int data_ind = 0;
  for(int i = 0; i < *csr_info.number_of_nodes; i++){
    for(int j = 0; j < adj_list[i].size(); j++){
      csr_info.col_index[data_ind] = adj_list[i][j];
      csr_info.influence[data_ind] = influence[i][j];
      data_ind++;
    }
  }

  return csr_info;
}
