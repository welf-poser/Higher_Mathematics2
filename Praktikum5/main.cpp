#include"CZufall.h"
#include"CLotto.h"
#include<iostream>
#include<ctime>

void print_vec(std::vector<int> val) {
	for (int i = 0; i < val.size(); i++) {
		std::cout << val[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	
	CZufall ztest;
	ztest.ausgabe_test(3,7,1000);

	std::cout << std::endl;
	
	
	CLotto test(8, 30, 4);
	
	
	clock_t start, ende;


	for (int i = 100; i < 100000000; i*=10) {
		std::cout << "N = "<< i << std::endl;
		start = clock();
		test.monte_carlo_sim(3, i, true);
		ende = clock();
		std::cout << "Normal:" << ende - start << "ms" << std::endl;
		start = clock();
		test.monte_carlo_sim_optimized(3, i, true);
		ende = clock();
		std::cout << "Optimized:" << ende - start << "ms" << std::endl << std::endl;

		start = clock();
		test.monte_carlo_sim(3, i, false);
		ende = clock();
		std::cout << "Normal:" << ende - start << "ms" << std::endl;
		start = clock();
		test.monte_carlo_sim_optimized(3, i, false);
		ende = clock();
		std::cout << "Optimzied:" << ende - start << "ms" << std::endl << std::endl;

		std::cout << std::endl;
	}
	

	

	return 0;
}