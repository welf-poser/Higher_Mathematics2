#include"CLotto.h"
#include"CZufall.h"
#include<stdlib.h>
#include<ctime>
#include<iostream>


//Constructor
CLotto::CLotto(int k, int n, int s) {
	this->k = k;
	this->n = n;

	if (s > 0) 
		srand(s);
	else
		srand((unsigned)std::time(0));
	tippzettel = draw();
}

//Getter and Setter
void CLotto::set_tippzettel(std::vector<int> tipp) {
	
	tippzettel = tipp;
}

std::vector<int> CLotto::draw() {
	CZufall rand_draw;
	std::vector<int> draw(k);

	int val;

	for (int i = 0; i < k; i++) {

		val = rand_draw.wert(0, n);

		for (int j = 0; j < i; j++) {

			if (draw.at(i) == val) {
				val = rand_draw.wert(0, n);
				j--;
			}
		}
		draw.at(i) = val;
	}
	return draw;
}

int CLotto::compare_draw(std::vector<int> tipp) {
	std::vector<int> draw_vec = draw();

	int out = 0;
	for (int i = 0; i < draw_vec.size(); i++) {
		for (int j = 0; j < tipp.size(); j++) {
			if (draw_vec.at(i) == tipp.at(j)) {
				out++;
				break;
			}
		}
	}
	return out;
}

void CLotto::monte_carlo_sim(int r, int N, bool typ) {
	//Gleicher Tippzettel
	CZufall rand_draw;
	std::vector<int> result;
	if (typ) {
		for(int i = 0; i < N; i++){
			result.push_back(compare_draw(tippzettel));
		}
		std::cout << "Modus: Gleicher Tippzettel" << std::endl;
	}
	//Immer verschiedener Tippzettel
	else {
		for(int i = 0; i < N; i++){
			set_tippzettel(draw());
			result.push_back(compare_draw(tippzettel));
		}
		std::cout << "Modus: Unterschiedlicher Tippzettel" << std::endl;
	}
	
	//Auswertung
	int hit = 0;
	for (int i = 0; i < N; i++) {

		if (result.at(i) == r) {
			hit++;
		}
	}
	


	double percent = 0;
	if (hit != 0)
		percent = (double(hit)/double(N)) * 100.0;

	std::cout << "Die Wahrscheinlichkeit " << r << " Treffer mit " << k << " Wahlmoeglichkeiten aus " << n << " Zahlen zu erreichen liegt bei " << percent << "%" << std::endl;
}