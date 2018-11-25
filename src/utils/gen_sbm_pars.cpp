using namespace std;

// this only generate a sbm with 'opinion leaders'
sbm_parameters gen_sbm_pars(const n_nodes& num_nodes, const int& n_communities, const n_nodes& e_leaders,
 const n_nodes& e_n_friends, const double& leader_influence){
	sbm_parameters sbm_pars;
	sbm_pars.number_of_nodes = num_nodes;

	double p_leader = e_leaders/((double) num_nodes);

  sbm_pars.class_probability = vector<double>(n_communities * 2);
  for(int i = 0; i < n_communities; i++){
  	// 'plane' subjects
  	sbm_pars.class_probability[i] = (1 - p_leader) * n_communities * 1000;
  	sbm_pars.class_probability[i + n_communities] = p_leader * n_communities * 1000;
  }
  sbm_pars.class_probability = random_dirichlet(sbm_pars.class_probability);

  sbm_pars.link_probability_matrix = vector<vector<double>>(2 * n_communities);

  double communities_link;
  for(int i = 0; i< n_communities; i++){
    sbm_pars.link_probability_matrix[i] = vector<double>(2 * n_communities);
    sbm_pars.link_probability_matrix[i + n_communities] = vector<double>(2 * n_communities);
    // give them values...
    for(int j = 0; j < n_communities; j++){
    	if(i < j) continue;
    	communities_link = random_uniform() * 2;
    	sbm_pars.link_probability_matrix[i][j] = sbm_pars.link_probability_matrix[j][i] = communities_link * e_n_friends / ((double) num_nodes);
    	sbm_pars.link_probability_matrix[i][j + n_communities] = sbm_pars.link_probability_matrix[j + n_communities][i] = 
    	sbm_pars.link_probability_matrix[i + n_communities][j + n_communities] = 
    	sbm_pars.link_probability_matrix[j + n_communities][i + n_communities] = communities_link * leader_influence;
    }
  }

  return sbm_pars;
}