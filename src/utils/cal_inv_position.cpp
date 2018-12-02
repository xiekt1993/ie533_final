int *cal_inv_position(sparse_csr_weighted csr_info){
  const int& num_nodes = *csr_info.number_of_nodes;
  const int& num_links = csr_info.row_ptr[num_nodes];

  int *inv_position = new int[num_links];
  int current_index;
  int inv_index;
  int n_linked_nodes;
  int n_linked_nodes_2;
  int node_2_ind;

  for(int node = 0; node < num_nodes; node++){
    n_linked_nodes = csr_info.row_ptr[node + 1] - csr_info.row_ptr[node];
    for(int node_2 = 0; node_2 < n_linked_nodes; node_2++){
      current_index = csr_info.row_ptr[node] + node_2;
      node_2_ind =  csr_info.col_index[current_index];
      n_linked_nodes_2 = csr_info.row_ptr[node_2_ind + 1] - csr_info.row_ptr[node_2_ind];
      for(int node_inv = 0; node_inv < n_linked_nodes_2; node_inv++){
        inv_index = csr_info.row_ptr[node_2_ind] + node_inv;
        if((csr_info.col_index[inv_index]) == node) inv_position[current_index] = inv_index;
        break;
      }
    }
  }

  return inv_position;
}
