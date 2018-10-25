#include "../src/include.h"

using namespace std;

int main(){
  int a = random_bernoulli(0.5);
  cout << a << endl;

  vector<double> dir_pars(10, 1);
  dir_pars = random_dirichlet(dir_pars);

  cout << random_uniform() << endl;

  for(auto it = dir_pars.begin(); it < dir_pars.end(); it++) cout << *it << " ";
  cout << endl;

  return 0;
}
