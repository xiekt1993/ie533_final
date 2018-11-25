#include "../src/include.h"
using namespace std;

network_info generate_info(int n, int a, double b, double c){
    network_info info;
    info.nodes_types=new node_type[n];
    for (int i=1;i<n;i++){
        info.nodes_types[i]=(node_type)i;
    }
    info.time_length=new uint8_t();
    *info.time_length=a;
    info.n_threshold=new double();
    *info.n_threshold=b;
    info.p_threshold=new double();
    *info.p_threshold=c;
    return info;
}

int main(){
  sbm_parameters par1;
  par1.number_of_nodes = 5;
  par1.class_probability = vector<double> (2, 0.5);
  par1.link_probability_matrix = vector<vector<double> > (2);
  par1.link_probability_matrix[0] = vector<double>(2, 0.5);
  par1.link_probability_matrix[1] = vector<double>(2, 0.5);

  adjacency_list adj_list1 = generate_sbm(par1);
  influence_list inf_list1 = generate_influence(adj_list1);
  sparse_csr_weighted csr_info1 = to_sparse(adj_list1,inf_list1);
  network_info network_info1=generate_info(par1.number_of_nodes,7,10.07,10.07);
  string file="csr_save_test.txt";
  string info_file="info_save_test.txt";
  save_csr(csr_info1,file);
  save_info(network_info1,info_file,5);
  sparse_csr_weighted csr_info3=read_csr(file);
  network_info network_info2=read_info(info_file,par1.number_of_nodes);
  cout<<*csr_info3.number_of_nodes<<endl;
  for(int i=0;i<*csr_info3.number_of_nodes;i++){
    cout<<csr_info3.confidence[i]<<" ";
  }
  cout<<endl;
  for(int i=0;i<*csr_info3.number_of_nodes+1;i++){
    cout<<csr_info3.row_ptr[i]<<" ";
  }
  cout<<endl;
  for(int i=0;i<csr_info3.row_ptr[*csr_info3.number_of_nodes];i++){
    cout<<csr_info3.influence[i]<<" ";
  }
  cout<<endl;
  for(int i=0;i<csr_info3.row_ptr[*csr_info3.number_of_nodes];i++){
    cout<<csr_info3.col_index[i]<<" ";
  }
  cout<<endl;
  for(int i=0;i<par1.number_of_nodes;i++){
    cout<<network_info2.nodes_types[i]<<" ";
  }
  cout<<endl;
  cout<<(int)*network_info2.time_length<<endl;
  cout<<*network_info2.n_threshold<<endl;
  cout<<*network_info2.p_threshold<<endl;
  return 0;
}
