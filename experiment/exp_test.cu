#include "../src/cuda_include.h"

int main(){
  string test_csr_filename = "test_csr.data";
  string test_info_filename = "test_info.data";

  network_in_device nw_host = read_network(test_info_filename, test_csr_filename);

  device_cal_evidence_host(nw_host.csr_info, nw_host.nw_info);

  return 0;
}