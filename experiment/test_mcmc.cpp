#include "../src/include.h"

int main(){
  sbm_parameters test_sbm_pars = gen_sbm_pars(10, 1, 1, 1, 0.5);
  adjacency_list adj_list = generate_sbm(test_sbm_pars);

  influence_list true_influence = ;

  mcmc();
  
  return 0;
}
