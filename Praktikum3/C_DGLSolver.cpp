#include"C_DGLSolver.h"
#include<iostream>


//Constructors
C_DGLSolver::C_DGLSolver(CMyVector(*f_DGL_System)(CMyVector y, double x))
{
	nterOrdnung = false;
	
	this->f_DGL_System = f_DGL_System;
	this->f_DGL_nterOrdnung = nullptr;
}

C_DGLSolver::C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVector y, double x)) {
	
	nterOrdnung = true;
	
	this->f_DGL_System = nullptr;
	this->f_DGL_nterOrdnung = f_DGL_nterOrdnung;
}

//Getter
bool C_DGLSolver::get_nterOrdnung() { return nterOrdnung; }

//Y-Vector sind die Y-Werte
CMyVector C_DGLSolver::ableitungen(CMyVector y, double x) {
	//DGL-System wurde übergeben
	if (!nterOrdnung) {
		return f_DGL_System(y, x);
	}
	//DGL höherer Ordnung wurde übergeben
	else{
		CMyVector result(y.getDim());

		for (int i = 0; i < y.getDim()-1; i++) {
			result.setComponent(i, y.getComponent(i+1));
		} 
		result.setComponent(y.getDim()-1, f_DGL_nterOrdnung(y,x));
		return result;
	}
}

//Solution procedures
void C_DGLSolver::euler_print(double xStart, double xEnd, int steps, CMyVector y_Start) {

	double h = (xEnd - xStart) / steps;

	for (int i = 0; i < steps; i++) {
		std::cout << "Schritt " << i << ":  ***********************************************" << std::endl << std::endl;
		std::cout << "x = " << xStart << std::endl;
		std::cout << "y = " << y_Start.vecToString() << std::endl;
		std::cout << "y'= " << ableitungen(y_Start, xStart).vecToString() << std::endl;
		y_Start = y_Start + ableitungen(y_Start, xStart) * h;
		xStart += h;
		std::cout << std::endl;
	}
	std::cout << "Ende bei:" << std::endl;
	std::cout << "x = " << xStart<< std::endl;
	std::cout << "y = " << y_Start.vecToString() << std::endl;
}

void C_DGLSolver::heun_print(double xStart, double xEnd, int steps, CMyVector y_Start) {

	double h = (xEnd - xStart) / steps;
	std::cout << "h = " << h << std::endl << std::endl;

	
	CMyVector y_orig_abl(y_Start.getDim());
	CMyVector y_Test(y_Start.getDim());
	CMyVector y_Test_abl(y_Start.getDim());
	CMyVector y_Mittel = (y_Start.getDim());


	for (int i = 0; i < steps; i++) {

		std::cout << "Schritt " << i << ":  ***********************************************" << std::endl << std::endl;
		std::cout << "x = " << xStart << std::endl;
		std::cout << "y = " << y_Start.vecToString() << std::endl;
		y_orig_abl = ableitungen(y_Start, xStart);
		std::cout << "y'_orig = " << y_orig_abl.vecToString() << std::endl;
		std::cout << std::endl;

		y_Test = y_Start + ableitungen(y_Start, xStart) * h;
		xStart += h;
		std::cout << "y_Test = " << y_Test.vecToString() << std::endl;
		y_Test_abl = ableitungen(y_Test, xStart);
		std::cout << "y'_Test = " << y_Test_abl.vecToString() << std::endl;
		std::cout << std::endl;
		y_Mittel = (y_orig_abl + y_Test_abl) * 0.5;
		std::cout << "y'_Mittel = " << y_Mittel.vecToString() << std::endl;
		y_Start = y_Start + (h*y_Mittel);
		std::cout << std::endl;
	}

	std::cout << "Ende bei:" << std::endl;
	std::cout << "x = " << xStart << std::endl;
	std::cout << "y = " << y_Start.vecToString() << std::endl;
}

CMyVector C_DGLSolver::euler(double xStart, double xEnd, int steps, CMyVector y_Start) {
	
	double h = (xEnd - xStart) / steps;

	for (int i = 0; i < steps; i++) {
		y_Start = y_Start + ableitungen(y_Start, xStart) * h;
		xStart += h;
	}
	return y_Start;
}

CMyVector C_DGLSolver::heun(double xStart, double xEnd, int steps, CMyVector y_Start) {

	double h = (xEnd - xStart) / steps;

	CMyVector y_orig_abl(y_Start.getDim());
	CMyVector y_Test(y_Start.getDim());
	CMyVector y_Test_abl(y_Start.getDim());
	CMyVector y_Mittel(y_Start.getDim());

	for (int i = 0; i < steps; i++) {

		y_orig_abl = ableitungen(y_Start, xStart);

		y_Test = y_Start + y_orig_abl * h;
		xStart += h;

		y_Test_abl = ableitungen(y_Test, xStart);

		y_Mittel = (y_orig_abl + y_Test_abl) * 0.5;

		y_Start = y_Start + (y_Mittel * h);
	}
	return y_Start;
}

CMyVector C_DGLSolver::runge_kutta(double xStart, double xEnd, int steps, CMyVector y_Start) {

	double h = (xEnd - xStart) / steps;

	CMyVector y_orig_abl(y_Start.getDim());
	CMyVector y_Test(y_Start.getDim());
	CMyVector y_Test_abl(y_Start.getDim());
	CMyVector y_Mittel(y_Start.getDim());

	for(int i = 0; i < steps; i++){

		y_orig_abl = ableitungen(y_Start, xStart);

		y_Test = y_Start + y_orig_abl*(h / 3);
		xStart += (h/3);


		y_Test_abl = ableitungen(y_Test, xStart);

		y_Test = y_Start + y_Test_abl * (h*2/3);
		xStart += (h/3);

		y_Test_abl = ableitungen(y_Test, xStart);

		y_Mittel = (0.25*y_orig_abl + 0.75*y_Test_abl) ;

		y_Start = y_Start + (y_Mittel * h);
		xStart += (h / 3);
	}
	return y_Start;
}

