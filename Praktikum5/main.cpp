#include"CZufall.h"
#include"CLotto.h"
#include<iostream>

int main() {
	
	CZufall ztest;
	ztest.ausgabe_test(3,7,1000);

	std::cout << std::endl;
	
	
	CLotto test(5, 31,-1);

	for (int i = 100; i < 10000000; i*=10) {
		std::cout << "N = "<< i << std::endl;
		test.monte_carlo_sim(2, i, true);
		test.monte_carlo_sim(2, i, false);
		std::cout << std::endl;
	}

	return 0;
}