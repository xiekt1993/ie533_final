// still executed at host side..

simulation_single cp_to_host(network_in_device nw_device){
	simulation_single sim_ptr;

	n_nodes *num_nodes = new n_nodes;
	uint8_t *t_length = new uint8_t;

	cudaMemcpy(num_nodes, nw_device.csr_info.number_of_nodes,
	  sizeof(n_nodes), cudaMemcpyDeviceToHost);

  cudaMemcpy(t_length, nw_device.nw_info.time_length,
    sizeof(uint8_t), cudaMemcpyDeviceToHost);

  sim_ptr.evidence = new double[(*num_nodes) * (*t_length)];
  sim_ptr.activated_positive = new int[(*num_nodes) * (*t_length)];
  sim_ptr.activated_negative = new int[(*num_nodes) * (*t_length)];
  sim_ptr.total_activated_positive = new int[(*num_nodes)];
  sim_ptr.total_activated_negative = new int[(*num_nodes)];

  cudaMemcpy(sim_ptr.evidence, nw_device.sim_ptr.evidence,
    (*num_nodes) * (*t_length) * sizeof(double), cudaMemcpyDeviceToHost);
  cudaMemcpy(sim_ptr.activated_positive, nw_device.sim_ptr.activated_positive,
    (*num_nodes) * (*t_length) * sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(sim_ptr.activated_negative, nw_device.sim_ptr.activated_negative,
    (*num_nodes) * (*t_length) * sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(sim_ptr.total_activated_positive, nw_device.sim_ptr.total_activated_positive,
    (*num_nodes) * sizeof(int), cudaMemcpyDeviceToHost);
  cudaMemcpy(sim_ptr.total_activated_negative, nw_device.sim_ptr.total_activated_negative,
    (*num_nodes) * sizeof(int), cudaMemcpyDeviceToHost);

	return sim_ptr;
}