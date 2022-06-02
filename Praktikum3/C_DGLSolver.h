#pragma once
#include"CMyVector.h"


class C_DGLSolver {
private:
	//Function-Pointer
	CMyVector(*f_DGL_System)(CMyVector y, double x);
	double(*f_DGL_nterOrdnung)(CMyVector y, double x);

	//Which one is choosen 
	bool nterOrdnung;

	CMyVector ableitungen(CMyVector y, double x);
public:
	//Constructor
	C_DGLSolver(CMyVector(*f_DGL_System)(CMyVector y, double x));
	C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVector y, double x));

	//Getter
	bool get_nterOrdnung();

	//Solution procedures
	CMyVector euler(double xStart, double xEnd, int steps, CMyVector y_Start);
	CMyVector heun(double xStart, double xEnd, int steps, CMyVector y_Start);
	CMyVector runge_kutta(double xStart, double xEnd, int steps, CMyVector y_Start);

	void euler_print(double xStart, double xEnd, int steps, CMyVector y_Start);
	void heun_print(double xStart, double xEnd, int steps, CMyVector y_Start);

};