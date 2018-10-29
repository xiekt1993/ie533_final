#include "../src/include.h"

using namespace std;

int main(){
  sbm_parameters par1;
  par1.number_of_nodes = 5;
  par1.class_probability = vector<double> (2, 0.5);
  par1.link_probability_matrix = vector<vector<double>> (2);
  par1.link_probability_matrix[0] = vector<double>(2, 0.5);
  par1.link_probability_matrix[1] = vector<double>(2, 0.5);

  adjacency_list adj_list1 = generate_sbm(par1);
  cout << (int)adj_list1[0][0] << endl;
  return 0;
}
