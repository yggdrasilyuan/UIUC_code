#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <random>
#include <stdio.h>
#include <vector>
using namespace std;
#define CAUCHY_DENSITY(x) 1./(PI * (1 + x * x))
#define GAUSSIAN_DENSITY(x) 0.398942280375387*exp(-x*x/2.0)

unsigned seed = (unsigned)time(NULL);
default_random_engine generator(seed);
const double PI = 3.141592653589793238463;    //value of pi

double get_uniform()
{
  uniform_real_distribution<double> distribution(0., 1.);
  return distribution(generator);
}

double get_cauchy()
{
  return tan(PI * (get_uniform() - 0.5));
}

vector<int> generate(int no_of_trials)
{
  double y;
  vector<int> count(101, 0);
  for (int flag = 0; flag < no_of_trials; flag++)
  {
    y = get_cauchy();
    for (int flag = 0; flag <= 100; flag++)
      if ( (y >= ((float) (flag-51)/10)) && (y < ((float) (flag-50)/10)) )
        count[flag]++;
  }
  return count;
}




int main(int argc, const char* argv[])
{  
  int no_of_trials;
  int num=100;
  sscanf(argv[1], "%d", &no_of_trials);
  vector<int> count = generate(no_of_trials);
  vector<double> theory_cauchy(num+1, 0.);
  vector<double> theory_gaussian(num+1, 0.);
  vector<double> n(num+1, 0.);
  vector<double> cdf_cauchy(num, 0.);
  vector<double> exp_cdf(num, 0.);
  vector<double> experiment_cauchy(num+1, 0.);
  

  for (int flag = 0; flag <= num; flag++)
  {
    n[flag] = (flag - 50.) / 10.;
    theory_cauchy[flag] = (0.1 * CAUCHY_DENSITY((float) n[flag]));
    theory_gaussian[flag] = 0.1*GAUSSIAN_DENSITY((float) n[flag]);
  }

	for (int flag = 1; flag < num; flag++) {
    cdf_cauchy[flag] = cdf_cauchy[flag - 1] + (0.1 * CAUCHY_DENSITY((float) (flag - 50) / 10));
  }

	int sum = 0;
	for (int flag = 0; flag < num; flag++)
  {
		sum += count[flag];
    exp_cdf[flag] = sum / no_of_trials;
	}
  for (int flag = 0; flag <=100; flag++)
  {
    experiment_cauchy[flag] = ((float) count[flag]) / no_of_trials;
  }

  ofstream logfile("res.csv");
  if (logfile.is_open())
  {
    logfile << "n,Theory_Cauchy,Experiment_Cauchy,Theory_Gaussian";
    logfile << endl;
    for (int flag = 0; flag < n.size(); flag++)
    {
      logfile << n[flag] << "," << theory_cauchy[flag] << "," << experiment_cauchy[flag] << "," << theory_gaussian[flag] << endl;
    }
  }
  logfile.close();

  system("pause");
  return 0;
}