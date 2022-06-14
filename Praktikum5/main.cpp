#include"CZufall.h"
#include"CLotto.h"
#include<iostream>

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
	
	
	CLotto test(8, 30,-1);
	
	for (int i = 100; i < 10000000; i*=10) {
		std::cout << "N = "<< i << std::endl;
		test.monte_carlo_sim(3, i, true);
		test.monte_carlo_sim(3, i, false);
		std::cout << std::endl;
	}

	return 0;
}