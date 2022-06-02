#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <string>

class CMyVector {

private:
	std::vector<double> vec;
	int dim;

public:
	//Constructors
	CMyVector();
	CMyVector(int i);
	CMyVector(const CMyVector& x);


	//Getter and Setter
	void setDim(int i);
	int getDim();
	double getComponent(int i);
	void setComponent(int i, double comp);
	double getLength();


	//Operators
	CMyVector operator+(CMyVector b);
	CMyVector operator*(double lambda);
	CMyVector operator*(CMyVector x);
	CMyVector operator=(CMyVector x);


	//Print-functions
	void printVec();
	std::string vecToString();
};

CMyVector operator*(double lambda, CMyVector x);

