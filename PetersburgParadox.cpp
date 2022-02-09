#include<iostream>
#include<random>
#include<cmath>
#include<vector>
#include <algorithm>
using namespace std;

int main(){
	/* Author: Emily Jakobs
		Goal: illustrate the Petersburg paradox: If a gambler plays a game in which a coin is
		flipped until it lands on heads, with the gambler getting 2^n dollars, with n the number of 
		flips needed to get the heads, then the expected winnings doesn't converge.
	*/
	int num_samples = 500; //how many samples?
	int num_trials = 1e+6; //how many times do we play the game per sample?
	vector<double> avg_payoff; //using vectors here for easy sorting to find median; may replace with array
	for(int i = 0; i < num_samples; i++){
		avg_payoff.push_back(0);
	}

	//set random seed
	random_device rd;
	//init Mersenne Twistor
	mt19937 gen(rd());
	//uniform over 0,1
	uniform_int_distribution<> dis(0,1);

	cout << "Calculating payoffs: " << endl;
	for(int j = 0; j < num_samples; j++){
		if( j % (num_samples/10) == 0 ) cout << 100 * j/num_samples << " percent done." << endl;
		for(int i  = 0; i < num_trials; i++){
			bool done = false;
			double count = 1;
			while(!done){
				if(dis(gen) == 0){
					//if heads
					avg_payoff[j] = avg_payoff[j]+ pow(2,count);
					done = true;
				}
				else{
					count++;
				}
			}
		}
		avg_payoff[j] = avg_payoff[j] / num_trials; 
	}

	double mean = 0;
	double var = 0;
	double skewTop = 0;
	double skewBot = 0;
	double skew = 0;
	double kurt = 0;
	for(int k = 0; k < num_samples; k++){
		mean += avg_payoff[k];
	}
	mean /= num_samples;

	for(int k = 0; k < num_samples; k++){
		var += (avg_payoff[k] - mean)*(avg_payoff[k] - mean);
		skewTop += (avg_payoff[k] - mean)*(avg_payoff[k] - mean)*(avg_payoff[k] - mean);
		kurt += (avg_payoff[k] - mean)*(avg_payoff[k] - mean)*(avg_payoff[k] - mean)*(avg_payoff[k] - mean);
	}
	kurt *= num_samples/(var*var);
	skewBot = var / num_samples;
	skewBot = sqrt(skewBot * skewBot * skewBot);
	var /= (num_samples-1);
	skewTop /= num_samples;
	skew = skewTop/skewBot;
	


	sort(avg_payoff.begin(), avg_payoff.end());
	double median = avg_payoff[num_samples/2];
	
	cout << "Through " << num_samples << " samples of " << num_trials << " trials each, the sample means had the following properties: " << endl;
	cout << "Mean: " << mean << endl;
	cout << "Median: " << median << endl;
	cout << "Standard Deviation: " << sqrt(var) << endl;
	cout << "Range: " << avg_payoff[0] << " to " << avg_payoff[num_samples-1] << endl;
	cout << "Skewness: " << skew << endl;
	cout << "Excess Kurtosis: " << kurt -3 << endl;

	avg_payoff.clear(); //free memory

	return 0;

}
