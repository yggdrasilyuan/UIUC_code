#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <stdio.h>

#include <vector>
using namespace std;

unsigned seed = (unsigned) std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
const double PI = 3.141592653589793238463;    //value of pi

#define CAUCHY_DENSITY(x) 1./(PI * (1 + x * x))
#define GAUSSIAN_DENSITY(x) 0.398942280375387*exp(-x*x/2.0)

double get_uniform()
{
  uniform_real_distribution<double> distribution(0., 1.);
  return distribution(generator);
}

double get_cauchy()
{
  return tan(PI * (get_uniform() - 0.5));
}

vector<int> gen_counts(int no_of_trials)
{
  double y;
  vector<int> count(101, 0);
  for (int i = 0; i < no_of_trials; i++)
  {
    y = get_cauchy();
    for (int j = 0; j <= 100; j++)
      if ( (y >= ((float) (j-51)/10)) && (y < ((float) (j-50)/10)) )
        count[j]++;
  }
  return count;
}

void writeout(vector<double> &n ,vector<double> &theory_cauchy, vector<double> &exp_cauchy, vector<double> &theory_gaussian)
{
  ofstream logfile("res.csv");
  if (logfile.is_open())
  {
    logfile << "n,Theory_Cauchy,Experiment_Cauchy,Thoery_Gaussian";
    logfile << "\n";
    for (int i = 0; i < n.size(); i++)
    {
      logfile << n[i] << "," << theory_cauchy[i] << "," << exp_cauchy[i] << "," << theory_gaussian[i] << "\n";
    }
  }
  logfile.close();
}



int main(int argc, const char* argv[])
{
  vector<double> x(101, 0.);
  vector<double> cdf_cauchy(100, 0.);
  vector<double> exp_cdf(100, 0.);
  vector<double> exp_pdf(101, 0.);
  int no_of_trials;

  sscanf(argv[1], "%d", &no_of_trials);
  vector<int> count = gen_counts(no_of_trials);

  vector<double> pdf_cauchy(101, 0.);
  vector<double> pdf_normal(101, 0.);
  for (int i = 0; i <= 100; i++)
  {
    x[i] = (i - 50.) / 10.;
    pdf_cauchy[i] = (0.1 * CAUCHY_DENSITY((float) x[i]));
    pdf_normal[i] = 0.1*GAUSSIAN_DENSITY((float) x[i]);
  }

	for (int j = 1; j < 100; j++) {
    cdf_cauchy[j] = cdf_cauchy[j - 1] + (0.1 * CAUCHY_DENSITY((float) (j - 50) / 10));
  }

	int sum = 0;
	for (int j = 0; j < 100; j++)
  {
		sum += count[j];
    exp_cdf[j] = sum / no_of_trials;
	}
  for (int i = 0; i <=100; i++)
  {
    exp_pdf[i] = ((float) count[i]) / no_of_trials;
  }

  writeout(x, pdf_cauchy, exp_pdf, pdf_normal);
  system("pause");
  return 0;
}