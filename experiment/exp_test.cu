#include "../src/cuda_include.h"

using namespace std;

int main(){
  string test_csr_filename = "test_csr.data";
  string test_info_filename = "test_info.data";

  network_in_device nw_host = read_network(test_info_filename, test_csr_filename);

  simulation_single sim_ptr = device_cal_evidence_host(nw_host.csr_info, nw_host.nw_info);
  for(int i = 0; i < 20; i ++) cout << sim_ptr.evidence[i] << "  ";
  cout << endl;

  return 0;
}