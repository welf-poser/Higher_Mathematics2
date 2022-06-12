#include"CZufall.h"
#include"CLotto.h"
#include<iostream>

int main() {

	CZufall ztest;
	ztest.ausgabe_test(3,7,1000);

	std::cout << std::endl;

	CLotto test(5, 31,-1);
	test.monte_carlo_sim(2, 10000000, true);
	test.monte_carlo_sim(2, 10000000, false);

	return 0;

}