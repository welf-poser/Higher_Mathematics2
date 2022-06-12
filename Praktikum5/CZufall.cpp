#include"CZufall.h"
#include<stdlib.h>
#include<vector>
#include<iostream>
#include<ctime>


int CZufall::wert(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void CZufall::initialisiere(int s) {
	srand(s);
	//Why not srand((unsigned)time(0)); ??
}

void CZufall::test(int a, int b, int N) {
	std::vector<int> number((b-a)+1);
	int val;
	for(int i = 0; i < N; i++){
		val = wert(a, b);
		int position = b % val;
		number.at(val -a) = number.at(val -a)+1;
	}

	int i = 0;
	for (a; a <= b; a++) {
		
		std::cout << "Die Zahl " << a << " kam " << number.at(i) << " mal vor." << std::endl;
		i++;
	}
}

void CZufall::test_falsch(int a, int b, int N) {
	std::vector<int> number((b - a) + 1);
	int val;
	for (int i = 0; i < N; i++) {
		initialisiere((unsigned)time(0));
		val = wert(a, b);
		int position = b % val;
		number.at(val - a) = number.at(val - a) + 1;
	}

	int i = 0;
	for (a; a <= b; a++) {

		std::cout << "Die Zahl " << a << " kam " << number.at(i) << " mal vor." << std::endl;
		i++;
	}
}

void CZufall::ausgabe_test(int a, int b, int N) {
	CZufall test;
	//Aufgabe a)
	test.initialisiere(3);
	std::cout << "Erste Ausgabe mit gleichem s:" << std::endl;
	test.test(a, b, N);
	std::cout << std::endl << "Zweite Ausgabe mit gleichem s:" << std::endl;
	test.initialisiere(3);
	test.test(a, b, N);

	//Aufgabe b)
	test.initialisiere(1);
	std::cout << std::endl << "Erste Ausgabe mit verschiedenen s:" << std::endl;
	test.test(a, b, N);

	test.initialisiere(2);
	std::cout << std::endl << "Zweite Ausgabe mit verschiedenen s:" << std::endl;
	test.test(a, b, N);

	//Aufgabe c)
	test.initialisiere((unsigned)time(0));
	std::cout << std::endl << "Erste Ausgabe mit s = (unsigned)time(0):" << std::endl;
	test.test(a, b, N);

	test.initialisiere((unsigned)time(0));
	std::cout << std::endl << "Zweite Ausgabe mit s = (unsigned)time(0):" << std::endl;
	test.test(a, b, N);

	//Aufgabe d)
	std::cout << std::endl << "Ausgabe von test_falsch" << std::endl;
	test.test_falsch(a, b, N);
}



