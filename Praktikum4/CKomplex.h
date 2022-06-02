#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <string>

class CKomplex{

private:
	double real;
	double ima;

public:
	//Constructors
	CKomplex();
	CKomplex(double a, double b);
	CKomplex(double phi);
	CKomplex(const CKomplex& x);

	//Getter
	double re();
	double im();

	//Operators
	CKomplex operator+(CKomplex b);
	CKomplex operator-(CKomplex b);
	CKomplex operator*(double lambda);
	CKomplex operator*(CKomplex x);
	CKomplex operator=(CKomplex x);
	CKomplex operator+=(CKomplex x);

	//Helper-Functions

	//Gibt den Betrag der komplexen Zahl zurück
	double abs();

	//Print-functions
	void printKomp();
	std::string to_string();
};

	CKomplex operator*(double lambda, CKomplex x);