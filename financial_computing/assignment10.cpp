#include <fstream>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;

unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);
double get_uniform()
{
    std::uniform_real_distribution <double> distribution(0, 1.0);
    double number = distribution(generator);
    return (number);
}

double risk_free_rate, strike_price, initial_stock_price;
double expiration_time, volatility, barrier_price;
int num_of_trials, num_of_divs;

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

double call_BSM(const double& S, const double& K,const double& r, const double& sigma, const double& time)      
{
    double time_sqrt = sqrt(time);
    double d1 = (log(S / K) + r * time) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
    double d2 = d1 - (sigma * time_sqrt);
    return S * N(d1) - K * exp(-r * time) * N(d2);
};

double put_BSM(const double& S, const double& K, const double& r, const double& sigma, const double& time)
{
    double time_sqrt = sqrt(time);
    double d1 = (log(S / K) + r * time) / (sigma * time_sqrt) + 0.5 * sigma * time_sqrt;
    double d2 = d1 - (sigma * time_sqrt);
    return K * exp(-r * time) * N(-d2) - S * N(-d1);
};

double ep_out_call()
{
    // I took this formula from Wilmott, Howison and Dewynne, "The Mathematics of Financial Derivatives"
    double K = (2 * risk_free_rate) / (volatility * volatility);
    double A = call_BSM(initial_stock_price, strike_price,
        risk_free_rate, volatility, expiration_time);
    double B = (barrier_price * barrier_price) / initial_stock_price;
    double C = pow(initial_stock_price / barrier_price, -(K - 1));
    double D = call_BSM(B, strike_price, risk_free_rate, volatility, expiration_time);
    return (A - D * C);
}

double ep_in_put()
{
    double r = risk_free_rate;
    double T = expiration_time;
    double sigma = volatility;
    double lambda = (r + ((sigma * sigma) / 2)) / (sigma * sigma);
    double temp = 2 * lambda - 2.0;
    double x1 = (log(initial_stock_price / barrier_price) / (sigma * sqrt(T))) + (lambda * sigma * sqrt(T));
    double y = (log(barrier_price * barrier_price / (initial_stock_price * strike_price)) / (sigma * sqrt(T))) + (lambda * sigma * sqrt(T));
    double y1 = (log(barrier_price / initial_stock_price) / (sigma * sqrt(T))) + (lambda * sigma * sqrt(T));
    return (-initial_stock_price * N(-x1) + strike_price * exp(-r * T) * N(-x1 + sigma * sqrt(T)) +
        initial_stock_price * pow(barrier_price / initial_stock_price, 2 * lambda) * (N(y) - N(y1)) -
        strike_price * exp(-r * T) * pow(barrier_price / initial_stock_price, temp) * (N(y - sigma * sqrt(T)) - N(y1 - sigma * sqrt(T))));
}

double ep_out_put()
{
    double vanilla_put = put_BSM(initial_stock_price, strike_price,
        risk_free_rate, volatility, expiration_time);
    double put_down_in = ep_in_put();
    return (vanilla_put - put_down_in);
}

int main(int argc, const char* argv[]) {
    sscanf(argv[1], "%lf", &expiration_time);
    sscanf(argv[2], "%lf", &risk_free_rate);
    sscanf(argv[3], "%lf", &volatility);
    sscanf(argv[4], "%lf", &initial_stock_price);
    sscanf(argv[5], "%lf", &strike_price);
    sscanf(argv[6], "%d", &num_of_trials);
    sscanf(argv[7], "%d", &num_of_divs);
    sscanf(argv[8], "%lf", &barrier_price);

    const double delta_T = expiration_time / ((double)num_of_divs);
    const double delta_R = (risk_free_rate - 0.5 * pow(volatility, 2)) * delta_T;
    const double delta_SD = volatility * sqrt(delta_T);

    cout << "European Down-and-out Continuous Barrier Options Pricing via Monte Carlo Simulation" << endl;
    cout << "Expiration Time (Years) = " << expiration_time << endl;
    cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
    cout << "Volatility (%age of stock value) = " << volatility * 100 << endl;
    cout << "Initial Stock Price = " << initial_stock_price << endl;
    cout << "Strike Price = " << strike_price << endl;
    cout << "Barrier Price = " << barrier_price << endl;
    cout << "Number of Trials = " << num_of_trials << endl;
    cout << "Number of Divisions = " << num_of_divs << endl;
    cout << "--------------------------------" << endl;

    double put_option_price = 0.0;
    double call_option_price = 0.0;
    
    double put_option_price_adj = 0.0;
    double call_option_price_adj = 0.0;
    for (int i = 0; i < num_of_trials; i++)
    {
        double current_SP1 = initial_stock_price;
        double current_SP2 = initial_stock_price;
        double current_SP3 = initial_stock_price;
        double current_SP4 = initial_stock_price;

        double current_SP1_adj = initial_stock_price;
        double current_SP2_adj = initial_stock_price;
        double current_SP3_adj = initial_stock_price;
        double current_SP4_adj = initial_stock_price;

        for (int j = 0; j < num_of_divs; j++)
        {
            // create the unit normal variates using the Box-Muller Transform
            double x = get_uniform();
            double y = get_uniform();
            double a = sqrt(-2.0 * log(x)) * cos(6.283185307999998 * y);
            double b = sqrt(-2.0 * log(x)) * sin(6.283185307999998 * y);

            // check if the current_SP > barrier price ?

            current_SP1 = ((current_SP1 * exp(delta_R + delta_SD * a)) > barrier_price) ? (current_SP1 * exp(delta_R + delta_SD * a)) : 0;
            current_SP2 = ((current_SP2 * exp(delta_R - delta_SD * a)) > barrier_price) ? (current_SP2 * exp(delta_R - delta_SD * a)) : 0;
            current_SP3 = ((current_SP3 * exp(delta_R + delta_SD * b)) > barrier_price) ? (current_SP3 * exp(delta_R + delta_SD * b)) : 0;
            current_SP4 = ((current_SP4 * exp(delta_R - delta_SD * b)) > barrier_price) ? (current_SP4 * exp(delta_R - delta_SD * b)) : 0;

            current_SP1_adj = current_SP1_adj * exp(delta_R + delta_SD * a);
            current_SP2_adj = current_SP2_adj * exp(delta_R - delta_SD * a);
            current_SP3_adj = current_SP3_adj * exp(delta_R + delta_SD * b);
            current_SP4_adj = current_SP4_adj * exp(delta_R - delta_SD * b);
        }
        double pd1 = (current_SP1 != 0) ? 1 : 0;
        double pd2 = (current_SP2 != 0) ? 1 : 0;
        double pd3 = (current_SP3 != 0) ? 1 : 0;
        double pd4 = (current_SP4 != 0) ? 1 : 0;

        call_option_price += (max(0.0, current_SP1 - strike_price) * pd1 + max(0.0, current_SP2 - strike_price) * pd2 + max(0.0, current_SP3 - strike_price) * pd3 + max(0.0, current_SP4 - strike_price) * pd4) / 4.0;
        put_option_price += (max(0.0, strike_price - current_SP1) * pd1 + max(0.0, strike_price - current_SP2) * pd2 + max(0.0, strike_price - current_SP3) * pd3 + max(0.0, strike_price - current_SP4) * pd4) / 4.0;

        double pc1, pc2, pc3, pc4;
        pc1 = (initial_stock_price <= barrier_price || current_SP1_adj <= barrier_price) ? 1.0 : (exp((-2.0 / (volatility * volatility * expiration_time)) * log(initial_stock_price / barrier_price) * log(current_SP1_adj / barrier_price)));
        pc2 = (initial_stock_price <= barrier_price || current_SP2_adj <= barrier_price) ? 1.0 : (exp((-2.0 / (volatility * volatility * expiration_time)) * log(initial_stock_price / barrier_price) * log(current_SP2_adj / barrier_price)));
        pc3 = (initial_stock_price <= barrier_price || current_SP3_adj <= barrier_price) ? 1.0 : (exp((-2.0 / (volatility * volatility * expiration_time)) * log(initial_stock_price / barrier_price) * log(current_SP3_adj / barrier_price)));
        pc4 = (initial_stock_price <= barrier_price || current_SP4_adj <= barrier_price) ? 1.0 : (exp((-2.0 / (volatility * volatility * expiration_time)) * log(initial_stock_price / barrier_price) * log(current_SP4_adj / barrier_price)));

        call_option_price_adj += (max(0.0, current_SP1_adj - strike_price) * (1.0 - pc1) + max(0.0, current_SP2_adj - strike_price) * (1.0 - pc2) + max(0.0, current_SP3_adj - strike_price) * (1.0 - pc3) + max(0.0, current_SP4_adj - strike_price) * (1.0 - pc4)) / 4.0;
        put_option_price_adj += (max(0.0, strike_price - current_SP1_adj) * (1.0 - pc1) + max(0.0, strike_price - current_SP2_adj) * (1.0 - pc2) + max(0.0, strike_price - current_SP3_adj) * (1.0 - pc3) + max(0.0, strike_price - current_SP4_adj) * (1.0 - pc4)) / 4.0;

    }
    call_option_price = exp(-risk_free_rate * expiration_time) * (call_option_price / ((double)num_of_trials));
    put_option_price = exp(-risk_free_rate * expiration_time) * (put_option_price / ((double)num_of_trials));
    call_option_price_adj = exp(-risk_free_rate * expiration_time) * (call_option_price_adj / ((double)num_of_trials));
    put_option_price_adj = exp(-risk_free_rate * expiration_time) * (put_option_price_adj / ((double)num_of_trials));

    cout << "--------------------------------" << endl;
    cout << "The average Call Price by explict simulation = " << call_option_price << endl;
    cout << "The Call Price using (1-p)-adjustment term   = " << call_option_price_adj << endl;
    cout << "Theoretical Call Price                       = " << ep_out_call() << endl;

    cout << "--------------------------------" << endl;
    cout << "The average Put Price by explict simulation = " << put_option_price << endl;
    cout << "The Put Price using (1-p)-adjustment term   = " << put_option_price_adj << endl;
    cout << "Theoretical Put Price                      = " << ep_out_put() << endl;
    cout << "--------------------------------" << endl;

    return 0;
}
