#include <stdio.h>
#include <tuple>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <chrono>   
using namespace std;
using namespace chrono;


// input information of Option
int no_of_divisions; // number of stage
double expiration_time ,r_f, volatility, initial_price, strike_price; 

//parameters required by trinomial trees
double u, d, dt;
double prob_u, prob_d, prob_m;

//option type: E -> European, A -> American


void input(int argc, const char* argv[])
{
    if (argc == 7){
        sscanf_s(argv[1],"%lf" , &expiration_time);
        sscanf_s(argv[2],"%d" , &no_of_divisions);
        sscanf_s(argv[3],"%lf" , &r_f);
        sscanf_s(argv[4],"%lf" , &volatility);
        sscanf_s(argv[5],"%lf" , &initial_price);
        sscanf_s(argv[6],"%lf" , &strike_price);
    } else {
        cout << "The input does not follow the rule" << endl;
        exit(1);
    }
}


// function that calculate u,d and uptick probability, down prob, and middle prob
void cal_implicit_prams() {
    dt = expiration_time / no_of_divisions;
    u = exp(volatility * sqrt(2 * dt));
    d = 1./u;
    prob_u = pow( (exp(0.5 * r_f * dt) - exp(-volatility *sqrt(0.5 * dt)) ) / (exp(volatility*sqrt(0.5*dt)) - exp(-volatility*sqrt(0.5*dt))), 2);
    prob_d = pow( (exp(volatility * sqrt(0.5 * dt))- exp( 0.5 * r_f * dt) ) / (exp(volatility*sqrt(0.5*dt)) - exp(-volatility*sqrt(0.5*dt))), 2);
    prob_m = 1. - prob_u - prob_d;
}  

  // function that simulate trinomial trees.
double trinomial_model(const char PutCall)
{
    int z;
    if (PutCall == 'C')
        z = 1;
    else if (PutCall == 'P') 
        z = -1;

    vector<double> original_option_val(2*(no_of_divisions) + 1);

    original_option_val[0] = initial_price;

    //simulate the price and payoff for each stage
    //How the memorization works: in each stage, every value increase by u and only need to add two value:
    //one is the last value in the last stage, one is the last value in the last stage go down (decrease by d).
    for (int i = 1; i < no_of_divisions+1; i++) { 
        original_option_val[2*i] =  d * original_option_val[2*i-2];
        original_option_val[2*i-1] = original_option_val[2*i-2];
        
        for (int j = 0; j < 2*i-1; j++)
        original_option_val[j] *= u;
    }

    double comparision;
    vector<double> copy;
    copy.assign(original_option_val.begin(), original_option_val.end());
    // backward to find the expect return at every stage.
    for (int j = no_of_divisions-1; j > -1; j--)
    {
        for (int i = 0; i < 2 * j + 1; i++) {
       
            copy[i] = copy[i] * d;
            comparision = z*(copy[i] - strike_price); 
            if (j == no_of_divisions - 1) 
            original_option_val[i] = max(comparision, exp(-r_f*dt)*(prob_d*max(z*(original_option_val[i + 2]-strike_price), 0.) + prob_m*max(z*(original_option_val[i + 1]-strike_price),0.)+ prob_u*max(z*(original_option_val[i]-strike_price), 0.)));
            else 
            original_option_val[i] = max(comparision, exp(-r_f*dt)*(prob_d*original_option_val[i + 2] + prob_m*original_option_val[i + 1] + prob_u*original_option_val[i]));
        }
        
    }

    return original_option_val[0];
}

// function that calculate Black Sholes result for Put or Call Option.
double BS_model(const char PutCall)
{
    // lambda function to calculate the N
    auto N = [&](double z) {
        if (z > 6.0)  return 1.0;  // this guards against overflow 
        if (z < -6.0) return 0.0; 
        double b1 = 0.31938153; 
        double b2 = -0.356563782; 
        double b3 = 1.781477937; 
        double b4 = -1.821255978; 
        double b5 = 1.330274429; 
        double p = 0.2316419; 
        double c2 = 0.3989423; 
        double a = fabs(z); 
        double t = 1.0/(1.0+a*p); 
        double b = c2*exp((-z)*(z/2.0)); 
        double n = ((((b5*t+b4)*t+b3)*t+b2)*t+b1)*t; 
        n = 1.0-b*n; 
        if ( z < 0.0 ) n = 1.0 - n; 
        return n; 
    };

    double time_sqrt = sqrt(expiration_time);
    double d1 = (log(initial_price/strike_price)+r_f*expiration_time)/(volatility*time_sqrt) + 0.5*volatility*time_sqrt;
    double d2 = d1-(volatility*time_sqrt);
    if (PutCall == 'C') 
        return initial_price*N(d1) - strike_price*exp(-r_f*expiration_time)*N(d2);
    else 
        return strike_price*exp(-r_f*expiration_time)*N(-d2) - initial_price*N(-d1);
}

// The function that print out the information of the Option.
void output()
{
    cout << "expiration_time Time (Years) = " << expiration_time << endl;
    cout << "Number of Divisions = " << no_of_divisions << endl;
    cout << "Risk Free Interest Rate" << r_f << endl;
    cout << "Volatility (%age of stock value) = " << volatility << endl;
    cout << "Initial Stock Price ="  << initial_price << endl;
    cout << "Strike Price = " << strike_price << endl; 
    cout.width(75);
    cout.fill('-');
    cout << "\n";
    cout << "Up Factor =" << u << endl;
    cout << "Uptick Probability = " << prob_u << endl;
    cout << "Notick Probability = " << prob_m << endl;
	cout << "Downtick Probability = " << prob_d << endl;
    cout.width(75);
    cout.fill('-');
    cout << "\n";
}


void get_price()
{
    double put_price, call_price;
    cal_implicit_prams();
    // Calculate put and call price
    put_price = trinomial_model('P');
    call_price = trinomial_model('C');

    cout << "Memorized Recursive Trinomial " << "American" << " Option Pricing" << endl; 

    //print out the info of the Option
    output();

    // print out the result including BS model and Trinomial Trees
   
    cout << "Trinomial Price of an American Call Option = " << call_price << endl;
    cout << "Trinomial Price of an American Put Option = " << put_price << endl;
    cout.width(75);
    cout.fill('-');
    cout << "\n";
    // verifying by put call parity
    cout << "Verifying Put Call Parity initial_price + P - C = Kexp(-r*T)" << endl;
    cout << initial_price << " + " << put_price << " - " << call_price << " = " << strike_price << "exp(" << -r_f << " * " << "expiration_time)" << endl;

    if ((initial_price + put_price - call_price - strike_price * exp(-r_f * expiration_time)) > 1e-4){
        cout << initial_price + put_price - call_price << " ?=? " << strike_price * exp(-r_f * expiration_time) << endl; 
        cout << "Looks like Put Call Parity does Not hold" << endl;
    } else
        cout << initial_price + put_price - call_price << " = " << strike_price * exp(-r_f * expiration_time) << endl; 
    cout.width(75);
    cout.fill('-');
    cout << "\n";
}

int main(int argc, const char* argv[]){
    auto start = system_clock::now();
    input(argc,argv);
    get_price();
    auto end   = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout <<  "It costs " 
		<< double(duration.count()) * microseconds::period::num / microseconds::period::den 
		<< "second " << endl;
    return 0;
}


