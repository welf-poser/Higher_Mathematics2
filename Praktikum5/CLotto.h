#pragma once
#include<vector>

class CLotto {
private:
	std::vector<int> tippzettel;
	int k;
	int n;

public:
	//Constructor
	CLotto(int k, int n, int s);

	//Getter and Setter
	void set_tippzettel(std::vector<int> tipp);
	std::vector<int> get_tippzettel();

	std::vector<int> draw();
	int compare_draw(std::vector<int> tipp);
	void monte_carlo_sim(int r, int N, bool typ);
	std::vector<bool> draw_optimized();
	int compare_draw_optimized(std::vector<int> tipp);
	void monte_carlo_sim_optimized(int r, int N, bool typ);
};