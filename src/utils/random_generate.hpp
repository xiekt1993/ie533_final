#ifndef RAN_GEN
#define RAN_GEN

using namespace std;

uint8_t random_bernoulli(const double &p){
  random_device rd;
  mt19937 gen(rd());

  bernoulli_distribution d(p);

  return d(gen);
}

double random_uniform(void){
  random_device rd;
  mt19937 gen(rd());

  uniform_real_distribution<> dis(0.0, 1.0);

  return dis(gen);
}

r_dirichlet random_dirichlet(const r_dirichlet& pars){
  uint8_t length = pars.size();
  r_dirichlet random_dirichlet(length);

  random_device rd;
  mt19937 gen(rd());

  gamma_distribution<double> dis;
  double sum = 0;

  for(int i = 0; i < length; i++){
    dis = gamma_distribution<double>(pars[i], 1.0);
    sum += (random_dirichlet[i] = dis(gen));
  }

  for(int i = 0; i < length; i++) random_dirichlet[i] /= sum;

  return random_dirichlet;
}

uint8_t random_discrete(const vector<double>& prob){
  double p = random_uniform();
  uint8_t block = 0;
  while(p > 0){
    p -= prob[block];
    block++;
  }
  return --block;
}

#endif