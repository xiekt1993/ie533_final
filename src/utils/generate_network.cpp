adjacency_list generate_sbm(const sbm_parameters& sbm_pars){
  adjacency_list sbm_adj_list(sbm_pars.number_of_nodes);
  // generate an sbm according to the parameters

  return sbm_adj_list;
}

adjacency_list_weighted generate_weighted_sbm(const sbm_parameters& sbm_pars){
  adjacency_list sbm_adj_list = generate_sbm(sbm_pars);
  // generate a weighted sbm according to the parameters
  adjacency_list_weighted sbm_adj_list_weighted;

  return sbm_adj_list_weighted;
}
