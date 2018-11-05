// device utility to calculate target evidence
__device__
void device_cal_evidence_formula(double *weight_start, double *weight_end,
  double *evidence_start, double *evidence_end, double *previous_evidence,
  double *confidence, double *target){
  // initialization
  *target = *confidence * (*previous_evidence);
  while(weight_start < weight_end){
    *target += (*weigth_start * (*evidence_start));
    evidence_start ++;
    weight_start ++;
  }
  return;
}

__device__
void device_cal_evidence(network_in_device *nw_device, int &node_id, int &t){
  device_cal_evidence_formula(
    nw_device.csr_info.influence + nw_device.csr_info.row_ptr[node_id],
    nw_device.csr_info.influence + nw_device.csr_info.row_ptr[node_id + 1],
    nw_device.sim_ptr.evidence + ,
    nw_device.sim_ptr.evidence + ,
    nw_device.sim_ptr.evidence +
    nw_device.csr_info.confidence + ,
    nw_device.sim_ptr.evidence +
  )
  return;
}
