// this file only generate new confidence and influence

void random_proposal(sparse_csr_weighted &proposal_csr, sparse_csr_weighted &current_csr,
  const double&kappa){

  random_device rd;
  mt19937 gen(rd());

  gamma_distribution<double> dis;

  const int& num_nodes = *current_csr.number_of_nodes;
  double sum;

  for(int i = 0; i < num_nodes; i++){
    int &i_start = current_csr.row_ptr[i];
    int &i_end = current_csr.row_ptr[i + 1];
    dis = gamma_distribution<double>(current_csr.confidence[i] * kappa, 1.0);
    sum = (proposal_csr.confidence[i] = dis(gen));

    for(int j = i_start; j < i_end; j++){
      dis = gamma_distribution<double>(current_csr.influence[j] * kappa, 1.0);
      sum += (proposal_csr.influence[j] = dis(gen));
    }

    proposal_csr.confidence[i] /= sum;
    for(int j = i_start; j < i_end; j++) proposal_csr.influence[j] /= sum;
  }

  return;
}
