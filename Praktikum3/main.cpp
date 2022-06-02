#include"CMyVector.h";
#include"C_DGLSolver.h";


//Testfunktionen
CMyVector test_DGL_System(CMyVector y, double x){
	CMyVector result(y.getDim());

	result.setComponent(0, 2 * y.getComponent(1) - x * y.getComponent(0));
	result.setComponent(1, y.getComponent(0) * y.getComponent(1) - 2 * x * x * x);

	return result;
}

double test_DGL_dritter_Ordnung(CMyVector y, double x){
	return 2 * x * y.getComponent(1) * y.getComponent(2) + 2 * y.getComponent(0) * y.getComponent(0) * y.getComponent(1);
}

/*
double test_DGL_Nr3(CMyVector y, double x) {
	return 2 * x * y.getComponent(0) * y.getComponent(0) * y.getComponent(0) * y.getComponent(0) * y.getComponent(1) + x * x * x * y.getComponent(1) * y.getComponent(2);
}
*/


int main(){
	
	/*
	* E-Test Aufgabe 3
	*
	CMyVector y_Nr3(3);
	y_Nr3.setComponent(0, 1);
	y_Nr3.setComponent(1, 2);
	y_Nr3.setComponent(2, -1);

	C_DGLSolver solver_Nr3(test_DGL_Nr3);

	solver_Nr3.euler_print(1, 1.4, 2, y_Nr3);
	*/

	//Values for functiontesting
	CMyVector y_System(2);
	y_System.setComponent(0, 0);
	y_System.setComponent(1, 1);

	CMyVector y_thirdOrder(3);
	y_thirdOrder.setComponent(0, 1);
	y_thirdOrder.setComponent(1, -1);
	y_thirdOrder.setComponent(2, 2);

	
	//Initialize DGL-Solver
	C_DGLSolver solver_System(test_DGL_System);
	C_DGLSolver solver_thirdOrder(test_DGL_dritter_Ordnung);


	//Output Euler and Heun
	//solver_System.euler_print(0, 2, 100, y_System);
	//solver_System.heun_print(0, 2, 100, y_System);

	
	//Output comparison Euler, Heun and Runge-Kutta
	
	for(int i = 10; i <= 10000; i*=10){
	std::cout << "Abweichung bei Euler bei "<< i <<" Schritten: " << solver_thirdOrder.euler(1, 2, i, y_thirdOrder).getComponent(0) -0.5 <<std::endl;
	std::cout << "Abweichung bei Heun bei " << i << " Schritten: " << solver_thirdOrder.heun(1, 2, i, y_thirdOrder).getComponent(0) - 0.5 << std::endl;
	std::cout << "Abweichung bei Runge-Kutta bei " << i << " Schritten: " << solver_thirdOrder.runge_kutta(1, 2, i, y_thirdOrder).getComponent(0) - 0.5 << std::endl;
	std::cout << std::endl;
	}
	

	return 0;
}