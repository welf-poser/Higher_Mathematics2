#define _USE_MATH_DEFINES
#include<math.h>
#include <fstream>   
#include <vector>
#include"CKomplex.h"
#include"Functions.h"

std::vector<CKomplex> werte_einlesen(const std::string dateiname)
{
	int i, N, idx;
	double re, im;
	std::vector<CKomplex> werte;
	// File oeffnen
	std::ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const std::string dateiname, std::vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
	// File oeffnen
	std::ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << std::endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << std::endl;
	// File schliessen
	fp.close();
}

std::vector<CKomplex> transformation(std::vector<CKomplex> data, bool mode) {
	const double pi = M_PI;
	int j = -1;
	//Vorfaktor komplexe Foriertransformation / Rücktransformation
	if (!mode) {
		j = 1;
	}
	
	int N = data.size();
	std::vector<CKomplex> result;
	result.resize(N);

	CKomplex null(0, 0);
	for (int i = 0; i < N; i++)
		result[i] = null;

	for (int n = 0; n < N; n++) {
		CKomplex sum(0, 0);
		for (int k = 0; k < N; k++) {
			CKomplex e(j * (2 * pi * k * n) / N);

			sum += (data[k] * e);
		}
		result[n] = (1.0 / sqrt(N)) * sum;
	}
	return result;
}

double max_dif(std::vector<CKomplex> a, std::vector<CKomplex> b) {

	double max = 0;
	double result = 0;
	for (int i = 0; i < a.size(); i++) {
		result = (a[i] - b[i]).abs();
		

		if (max < result)
			max = result;
	}
	return max;
}

void vergleiche_epsilon() {
	std::vector<CKomplex> data = werte_einlesen("Daten_original.txt");
	std::vector<CKomplex> transformiert = transformation(data, 1);

	werte_ausgeben("default.txt", transformiert, -1);
	werte_ausgeben("e0_001.txt", transformiert, 0.001);
	werte_ausgeben("e0_01.txt", transformiert, 0.01);
	werte_ausgeben("e0_1.txt", transformiert, 0.1);
	werte_ausgeben("e1_0.txt", transformiert, 1.0);

	std::vector<CKomplex> def_trans = werte_einlesen("default.txt");
	std::vector<CKomplex> e0_001_trans = werte_einlesen("e0_001.txt");
	std::vector<CKomplex> e0_01_trans = werte_einlesen("e0_01.txt");
	std::vector<CKomplex> e0_1_trans = werte_einlesen("e0_1.txt");
	std::vector<CKomplex> e1_0_trans = werte_einlesen("e1_0.txt");

	std::vector<CKomplex> def = transformation(def_trans, 0);
	std::vector<CKomplex> e0_001 = transformation(e0_001_trans, 0);
	std::vector<CKomplex> e0_01 = transformation(e0_01_trans, 0);
	std::vector<CKomplex> e0_1 = transformation(e0_1_trans, 0);
	std::vector<CKomplex> e1_0 = transformation(e1_0_trans, 0);

	std::cout << "Maximale Abweichung bei Standart-Epsilon: " << max_dif(data, def) << std::endl;
	std::cout << "Maximale Abweichung bei epsilon=0.001: " << max_dif(data, e0_001) << std::endl;
	std::cout << "Maximale Abweichung bei epsilon=0.01: " << max_dif(data, e0_01) << std::endl;
	std::cout << "Maximale Abweichung bei epsilon=0.1: " << max_dif(data, e0_1) << std::endl;
	std::cout << "Maximale Abweichung bei epsilon=1:0: " << max_dif(data, e1_0) << std::endl;
}