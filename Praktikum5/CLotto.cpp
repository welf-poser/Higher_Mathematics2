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
		srand(time(NULL));
	tippzettel = draw();
}

//Getter and Setter
void CLotto::set_tippzettel(std::vector<int> tipp) {
	
	tippzettel = tipp;
}

std::vector<int> CLotto::get_tippzettel() {
	return tippzettel;
}

std::vector<int> CLotto::draw() {
	CZufall rand_draw;
	std::vector<int> draw(k);

	int val;

	for (int i = 0; i < k; i++) {

		val = rand_draw.wert(1, n);

		for (int j = 0; j < i; j++) {

			if (draw[j] == val) {
				val = rand_draw.wert(1, n);
				j= -1;
			}
		}
		draw[i] = val;
	}
	return draw;
}

std::vector<bool> CLotto::draw_optimized() {
	CZufall rand_draw;
	std::vector<bool> draw(n);

	int val;

	for (int i = 0; i < k; i++) {

		val = rand_draw.wert(1, n);

		for (int j = 0; j < i; j++) {

			if (draw[val-1]) {
				val = rand_draw.wert(1, n);
				j = -1;
			}
		}
		draw[val-1] = true;
	}
	return draw;
}

int CLotto::compare_draw(std::vector<int> tipp) {
	std::vector<int> draw_vec = draw();

	int out = 0;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (draw_vec[i] == tipp[j]) {
				out++;
				break;
			}
		}
	}
	return out;
}
int CLotto::compare_draw_optimized(std::vector<int> tipp) {
	std::vector<bool> draw_vec = draw_optimized();

	int out = 0;
	for (int i = 0; i < k; i++) {
		if (draw_vec[tipp[i]-1]) {
			out++;
		}
	}
	return out;
}

void CLotto::monte_carlo_sim(int r, int N, bool typ) {
	//Gleicher Tippzettel
	int hit = 0;
	if (typ) {
		for(int i = 0; i < N; i++){
			if (r == compare_draw(tippzettel))
				hit++;
		}
		//std::cout << "Modus: Gleicher Tippzettel" << std::endl;
	}
	//Immer verschiedener Tippzettel
	else {
		for(int i = 0; i < N; i++){
			set_tippzettel(draw());
			if (r == compare_draw(tippzettel))
				hit++;
		}
		//std::cout << "Modus: Unterschiedlicher Tippzettel" << std::endl;
	}

	//std::cout << "Die Wahrscheinlichkeit " << r << " Treffer mit " << k << " Wahlmoeglichkeiten aus " << n << " Zahlen zu erreichen liegt bei " << (double(hit) / double(N)) * 100.0 << "%" << std::endl;
}

void CLotto::monte_carlo_sim_optimized(int r, int N, bool typ) {
	//std::cout << "Monte-Carlo Optimized" << std::endl;

	//Gleicher Tippzettel
	int hit = 0;
	if (typ) {
		for (int i = 0; i < N; i++) {
			if (r == compare_draw_optimized(tippzettel))
				hit++;
		}
		//std::cout << "Modus: Gleicher Tippzettel" << std::endl;
	}
	//Immer verschiedener Tippzettel
	else {
		for (int i = 0; i < N; i++) {
			set_tippzettel(draw());
			if (r == compare_draw_optimized(tippzettel))
				hit++;
		}
		//std::cout << "Modus: Unterschiedlicher Tippzettel" << std::endl;
	}

	//std::cout << "Die Wahrscheinlichkeit " << r << " Treffer mit " << k << " Wahlmoeglichkeiten aus " << n << " Zahlen zu erreichen liegt bei " << (double(hit) / double(N)) * 100.0 << "%" << std::endl;
}