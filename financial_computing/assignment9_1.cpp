#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

double up_factor, uptick_prob, risk_free_interest_rate, strike_price, downtick_prob, notick_prob;
double initial_stock_price, expiration_time, volatility, forward_return;
int no_of_divisions;

double N(const double& z) {
	if (z > 6.0) { return 1.0; }; 
	if (z < -6.0) { return 0.0; };
	double b1 = 0.31938153;
	double b2 = -0.356563782;
	double b3 = 1.781477937;
	double b4 = -1.821255978;
	double b5 = 1.330274429;
	double p = 0.2316419;
	double c2 = 0.3989423;
	double a = fabs(z);
	double t = 1.0 / (1.0 + a * p);
	double b = c2 * exp((-z) * (z / 2.0));
	double n = ((((b5 * t + b4) * t + b3) * t + b2) * t + b1) * t;
	n = 1.0 - b * n;
	if (z < 0.0) n = 1.0 - n;
	return n;
};

double max(double a, double b)
{
    if (a>b)
        return a;
    else
        return b;
}


double option_price_put_black_scholes(const double& S, const double& K, const double& forward_return, const double& sigma, const double& T) {
	double T_sqrt = sqrt(T);
	double d1 = (log(S / K) + forward_return * T) / (sigma * T_sqrt) + 0.5 * sigma * T_sqrt;
	double d2 = d1 - (sigma * T_sqrt);
	return K * exp(-forward_return * T) * N(-d2) - S * N(-d1);
};

double option_price_call_black_scholes(const double& S,       
	const double& K,
	const double& forward_return,
	const double& sigma,
	const double& T) {
	double time_sqrt = sqrt(T);
	double d1 = (log(S / K) + forward_return * T) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
	double d2 = d1 - (sigma * time_sqrt);
	return S * N(d1) - K * exp(-forward_return * T) * N(d2);
};

double european_call_option(int k, int i, double** european_call)
{
	if (k == no_of_divisions)
		return max(0.0, (initial_stock_price * pow(up_factor, ((double)i)) - strike_price));
	if (european_call[k][no_of_divisions + i] == -1)
	{
		european_call[k][no_of_divisions + i] = (uptick_prob * european_call_option(k + 1, i + 1, european_call) +
			(notick_prob * european_call_option(k + 1, i, european_call)) +
			(downtick_prob * european_call_option(k + 1, i - 1, european_call))) / forward_return;
		return european_call[k][no_of_divisions + i];
	}
	else
	{
		return european_call[k][no_of_divisions + i];
	}
}

double european_put_option(int k, int i, double** european_put)
{
	if (k == no_of_divisions)
		return max(0.0, (strike_price - initial_stock_price * pow(up_factor, ((double)i))));
	if (european_put[k][no_of_divisions + i] == -1)
	{
		european_put[k][no_of_divisions + i] = (uptick_prob * european_put_option(k + 1, i + 1, european_put) +
			(notick_prob * european_put_option(k + 1, i, european_put)) +
			(downtick_prob * european_put_option(k + 1, i - 1, european_put))) / forward_return;
		return european_put[k][no_of_divisions + i];
	}
	else
	{
		return european_put[k][no_of_divisions + i];
	}
}

int main(int argc, char* argv[])
{

	sscanf(argv[1], "%lf", &expiration_time);
	sscanf(argv[2], "%d", &no_of_divisions);
	sscanf(argv[3], "%lf", &risk_free_interest_rate);
	sscanf(argv[4], "%lf", &volatility);
	sscanf(argv[5], "%lf", &initial_stock_price);
	sscanf(argv[6], "%lf", &strike_price);

	double** european_call;
	european_call = new double*[no_of_divisions];
	for (int i = 0; i < no_of_divisions; i++)
		european_call[i] = new double[2 * no_of_divisions + 1];
	for (int i = 0; i < no_of_divisions; i++)
		for (int j = 0; j < 2 * no_of_divisions + 1; j++)
			european_call[i][j] = -1;

	double** european_put;
	european_put = new double*[no_of_divisions];
	for (int i = 0; i < no_of_divisions; i++)
		european_put[i] = new double[2 * no_of_divisions + 1];
	for (int i = 0; i < no_of_divisions; i++)
		for (int j = 0; j < 2 * no_of_divisions + 1; j++)
			european_put[i][j] = -1;


	up_factor = exp(volatility * sqrt(2 * expiration_time / ((double)no_of_divisions)));
	forward_return = exp(risk_free_interest_rate * expiration_time / ((double)no_of_divisions));
	uptick_prob = pow(((sqrt(forward_return) - (1 / sqrt(up_factor))) / (sqrt(up_factor) - (1 / sqrt(up_factor)))), 2.0);
	downtick_prob = pow(((sqrt(up_factor) - sqrt(forward_return)) / (sqrt(up_factor) - (1 / sqrt(up_factor)))), 2.0);
	notick_prob = 1 - uptick_prob - downtick_prob;

	cout << "(Memoized) Recursive Trinomial European Option Pricing" << endl;
	cout << "Expiration Time (Years) = " << expiration_time << endl;
	cout << "Number of Divisions = " << no_of_divisions << endl;
	cout << "Risk Free Interest Rate = " << risk_free_interest_rate << endl;
	cout << "Volatility (%age of stock value) = " << volatility * 100 << endl;
	cout << "Initial Stock Price = " << initial_stock_price << endl;
	cout << "Strike Price = " << strike_price << endl;
	cout << "--------------------------------------" << endl;
	cout << "Up Factor = " << up_factor << endl;
	cout << "Uptick Probability = " << uptick_prob << endl;
	cout << "--------------------------------------" << endl;
	double call_price = european_call_option(0, 0, european_call);
	cout << "Trinomial Price of an European Call Option = " << call_price << endl;
	cout << "Call Price according to Black-Scholes = " <<
		option_price_call_black_scholes(initial_stock_price, strike_price, risk_free_interest_rate,
			volatility, expiration_time) << endl;
	cout << "--------------------------------------" << endl;
	double put_price = european_put_option(0, 0, european_put);
	cout << "Trinomial Price of an European Put Option = " << put_price << endl;
	cout << "Put Price according to Black-Scholes = " <<
		option_price_put_black_scholes(initial_stock_price, strike_price, risk_free_interest_rate,
			volatility, expiration_time) << endl;
	cout << "--------------------------------------" << endl;
	cout << "Verifying Put-Call Parity: S+P-C = Kexp(-forward_return*T)" << endl;
	cout << initial_stock_price << "+" << put_price << "-" << call_price << "=" << strike_price << "exp" << "(" <<
		-risk_free_interest_rate << "*" << expiration_time << ")" << endl;
	cout << initial_stock_price + put_price - call_price << " = " << strike_price * exp(-risk_free_interest_rate * expiration_time)<<endl;
	cout << "--------------------------------------" << endl;
}
