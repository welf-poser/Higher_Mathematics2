#include <vector>
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

class CMyVector {

private:
	vector<double> vec;
	int dim;

public:
	
	CMyVector();

	CMyVector(int i) {
		dim = i;
		setDim(i);
	}

	CMyVector(const CMyVector &x) {
		dim = x.dim;
		setDim(dim);
		for (int i = 0; i < x.dim; i++) {
			setComponent(i, x.vec.at(i));
		}
	}

	void setDim(int i) {
		dim = i;
		vec.resize(i, 0);
	}

	int getDim() {
		return dim;
	}

	double getComponent(int i) {
		return vec[i];
	};

	void setComponent(int i, double comp) {
		vec[i] = comp;
	}

	double getLength() {
		double sum = 0;
		for (int i = 0; i < vec.size(); i++) {
			sum += pow(vec[i], 2);
		}

		if (sum < 0) { sum *= -1; }

		return sqrt(sum);
	}

	CMyVector operator+(CMyVector b) {
		if (this->getDim() == b.getDim()) {
			CMyVector c(b.getDim());
			for (int i = 0; i < b.getDim(); i++) {
				c.setComponent(i, (this->getComponent(i) + b.getComponent(i)));
			}
			return c;
		}
	}

	CMyVector operator*(double lambda) {
		for (int i = 0; i < this->getDim(); i++) {
			this->setComponent(i, (this->getComponent(i) * lambda));
		}
		return *this;
	}

	CMyVector operator*(CMyVector x) {
		if (x.getDim() == this->getDim()) {
			CMyVector out(x.getDim());
			for (int i = 0; i < x.getDim(); i++) {
				out.setComponent(i, x.getComponent(i) * this->getComponent(i));
			}
			return out;
		}
	}

	CMyVector operator=(CMyVector x) {
		setDim(x.getDim());
		for (int i = 0; i < x.getDim(); i++) {
			setComponent(i,x.getComponent(i));
		}
		return *this;
	}

	void printVec() {
		cout << "( ";
		for (int i = 0; i < getDim(); i++) {
			cout << getComponent(i);
			if (i != getDim() - 1)
				cout << "; ";
		}
		cout << " )";
	}

	string vecToString() {
		string out;
		out += "( ";
		for (int i = 0; i < getDim(); i++) {
			out += to_string(getComponent(i));
			if (i != getDim() - 1)
				out += "; ";
		}
		out += " )";
		
		return out;
	}

};

CMyVector gradient(CMyVector x, double (*f)(CMyVector x)) {
	double h = pow(10, -8);
	CMyVector output(x.getDim());
	
	for (int i = 0; i < x.getDim(); i++) {
		CMyVector xh=* new CMyVector(x);
		xh.setComponent(i, x.getComponent(i) + h);

		output.setComponent(i, (f(xh) - f(x)) / h);
	}
	
	return output;
}

double betragVec(CMyVector x) {
	double underSqr = 0;
	for (int i = 0; i < x.getDim(); i++) {
		underSqr += pow(x.getComponent(i),2);
	}
	return sqrt(underSqr);
}

void gradientenverfahren(CMyVector x, double (*f)(CMyVector x), double lambda = 1.0) {
	for (int i = 0; i <= 25; i++) {

		cout << "Schritt " << i << " *********************************************" << endl;
		cout << "x = " << x.vecToString() << endl;
		cout << "lambda = " << lambda << endl;
		cout << "f(x) = " << f(x) << endl;
		CMyVector gradvec = gradient(x, f);
		cout << "grad f(x) = " << gradvec.vecToString() << endl;
		cout << "||grad f(x)|| = " << betragVec(gradvec) << endl << endl;

		if (betragVec(gradvec) < pow(10, -5)) {
			cout << "Ende wegen ||grad f(x)|| < 10^(-5)" << endl;
			return;
		}
		if (i == 25) {
			cout << "Ende wegen Schrittzahl = 25" << endl;
			return;
		}

		CMyVector x_neu(x.getDim());
		x_neu = x + gradvec * lambda;
		cout << "x_neu = " << x_neu.vecToString() << endl;
		cout << "f(x_neu) = " << f(x_neu) << endl << endl;
		
		CMyVector x_test = x_neu;
		//lambda verdoppeln wenn f(x_neu) > f(x)
		if (f(x_neu) > f(x)) {
			cout << "Test mit doppelter Schrittweite (lambda = " << lambda * 2 << ")" << endl;
			x_test = x + gradient(x ,f) * (2*lambda);

			cout << "x_test = " << x_test.vecToString() << endl;
			cout << "f(x_test) = " << f(x_test) << endl;
			if (f(x_test) > f(x_neu)) {
				lambda *= 2;
				cout << "verdoppele Schrittweite" << endl;
				x = x_test;
			}
			else {
				cout << "Weiter mit alter Schrittweite" << endl;
				x = x_neu;
			}
		}
		//lambda halbieren wenn f(x_neu) <= f(x)
		else if (f(x_neu) <= f(x)) {
			while(f(x_neu) <= f(x)){
				cout << "halbiere Schrittweite (lambda = " << lambda / 2 << ")" << endl;
				lambda /= 2;
				
				x_neu = x + gradient(x,f) * lambda;
				cout << "x_neu = " << x_neu.vecToString() << endl;
				cout << "f(x_neu) = " << f(x_neu) << endl;

			}
			x = x_neu;
		}
		cout << endl << endl;
	}
}

class CMyMatrix {

private:
	//m = vertikal
	int dim_vert;
	//n = horizontal
	int dim_hor;
	vector<CMyVector> matrix;
public:
	CMyMatrix(int hor, int vert) 
	{
		dim_vert = vert;
		dim_hor = hor;

		for (int i = 0; i < hor; i++) {
			matrix.push_back(CMyVector(vert));
		}
	}

	int getDim_vert() {
		return dim_vert;
	}

	int getDim_hor() {
		return dim_hor;
	}

	void setComp(int hor, int vert, double x) {
		matrix.at(hor).setComponent(vert, x);
	}

	double getComp(int hor, int vert) {
		return matrix.at(hor).getComponent(vert);
	}

	CMyMatrix invers() {
		try {
			if (this->dim_hor == 2 && this->dim_vert == 2) {
				if ((this->getComp(0, 0) * this->getComp(1, 1)) - (this->getComp(0, 1) * this->getComp(1, 0)) == 0)
					throw invalid_argument("Matrix war keine 2X2");
				else {
					CMyMatrix result(2, 2);
					double det = 1 / ((this->getComp(0, 0) * this->getComp(1, 1)) - (this->getComp(1, 0) * this->getComp(0, 1)));
					//a
					result.setComp(0, 0, det * this->getComp(1, 1));
					//b
					result.setComp(1, 0, det * (-this->getComp(1, 0)));
					//c
					result.setComp(0, 1, det * (-this->getComp(0, 1)));
					//d
					result.setComp(1, 1, det * this->getComp(0, 0));
					return result;
				}
			}
			else {
				throw invalid_argument("Determinante = 0");
			}
		}
		catch (exception e) {
			cout << "Fehler bem invertieren der Matrix" << endl;
			exit(EXIT_FAILURE);
		}
	}

	void printMatrix() {
		for (int i = 0; i < this->dim_vert; i++) {
			string res = "*( ";
			for (int j = 0; j < this->dim_hor; j++) {
				res += to_string(this->getComp(j, i));
				if (j == dim_hor - 1) {
					res += " )*\n";
				}
				else
					res += "; ";
			}
			cout << res;
		}
		cout << endl;
	}

	CMyVector operator*(CMyVector x) {
		if (this->getDim_hor() == x.getDim()) {
			CMyVector result(this->getDim_vert());
			for (int i = 0; i < this->getDim_vert(); i++) {
				double sum = 0;
				for (int j = 0; j < this->getDim_hor(); j++) {
					sum += this->getComp(j, i) * x.getComponent(j);
					result.setComponent(i, sum);
				}
			}
			return result;
		}
		else {
			throw invalid_argument("Keine passenden Dimentionen bei Matrix-Vector-Multiplikation");
			exit(EXIT_FAILURE);
		}
	}
};


CMyMatrix jacobi(CMyVector x, CMyVector (*f)(CMyVector y)) {
	CMyVector dummy = f(x);
	int vert = dummy.getDim();
	CMyMatrix jacobi(x.getDim(), vert);
	double h = pow(10, -4);

	//Loop vertikal
	for (int i = 0; i < vert; i++) {

		//Loop horizontal
		for (int j = 0; j < x.getDim(); j++) {
			CMyVector xh = x;
			xh.setComponent(j, x.getComponent(j) + h);
			jacobi.setComp(j,i, (f(xh).getComponent(i) - f(x).getComponent(i)) / h);
		}
	}
	return jacobi;
}

void newtonverfahren(CMyVector x, CMyVector(*f)(CMyVector y)) {
	
	for (int i = 0; i <= 50; i++) {

		cout << "Schritt " << i << " *********************************************" << endl;
		cout << "x = " << x.vecToString() << endl;
		cout << "f(x) = " << f(x).vecToString() << endl;

		if (betragVec(f(x)) < pow(10, -5)) {
			cout << "||f(x)|| = " << betragVec(f(x)) << endl;
			cout << "Ende wegen ||f(x)|| < 10^(-5)" << endl;
			return;
		}
		cout << endl;

		CMyMatrix jac = jacobi(x, f);

		cout << "Jacobimatrix:" << endl;
		jac.printMatrix();

		cout << "Inverse:" << endl;
		CMyMatrix inv = jac.invers();
		inv.printMatrix();

		CMyVector dx = inv * (f(x) * (-1));
		cout << "dx = " << dx.vecToString() << endl;

		cout << "||f(x)|| = " << betragVec(f(x)) << endl << endl;
		

		
		if (i == 50) {
			cout << "Ende wegen Schrittzahl = 50" << endl;
			return;
		}
		x = x + dx;
		
		cout << endl << endl;
	}
}

/*
CMyVector operator*(CMyMatrix a, CMyVector x) {
	if (a.getDim_hor() == x.getDim()) {
		CMyVector result(a.getDim_vert());
		for (int i = 0; i < a.getDim_vert(); i++) {
			double sum = 0;
			for (int j = 0; j < a.getDim_hor(); j++) {
				sum += a.getComp(j, i) * x.getComponent(j);
				result.setComponent(i, sum);
			}
		}
		return result;
	}
	else {
		throw invalid_argument("Keine passenden Dimentionen bei Matrix-Vector-Multiplikation");
		exit(EXIT_FAILURE);
	}
}
*/


CMyVector test_aufgabe2(CMyVector x) {
	CMyVector result(3);
	result.setComponent(0, x.getComponent(0) * x.getComponent(1) * exp(x.getComponent(2)));
	result.setComponent(1, x.getComponent(1) * x.getComponent(2) * x.getComponent(3));
	result.setComponent(2, x.getComponent(3));
	return result;
}

CMyVector test_aufgabe3(CMyVector x) {
	CMyVector result(2);
	result.setComponent(0, pow(x.getComponent(0), 3) * pow(x.getComponent(1), 3) - 2 * x.getComponent(1));
	result.setComponent(1, x.getComponent(0) - 2);
	return result;
}

//h(x,y)=x+y gradient (1,1)
double h(CMyVector x) {
	return (x.getComponent(0) + x.getComponent(1));
}

double f(CMyVector x) { 
	return sin(x.getComponent(0) * x.getComponent(1)) + sin(x.getComponent(0)) + cos(x.getComponent(1));
}

double g(CMyVector x) {
	return -(2 * pow(x.getComponent(0), 2) - 2 * x.getComponent(0) * x.getComponent(1) + pow(x.getComponent(1), 2) + pow(x.getComponent(2), 2) - 2 * x.getComponent(0) - 4 * x.getComponent(2));
}

void gradientenverfahren_f() {
	CMyVector vec(2);
	vec.setComponent(0, 0.2);
	vec.setComponent(1, -2.1);

	gradientenverfahren(vec, f);
}

void gradientenverfahren_g() {
	CMyVector vec(3);
	vec.setComponent(0, 0);
	vec.setComponent(1, 0);
	vec.setComponent(2, 0);

	gradientenverfahren(vec, g, 0.1);
}

int main() {
	/*
	//gradientenverfahren_f();
	//gradientenverfahren_g();

	CMyMatrix test_mult(3, 2);
	CMyVector test_vec(3);
	
	//(2,3,-1)
	//(1,0,-1)
	test_mult.setComp(0, 0, 2);
	test_mult.setComp(1, 0, 3);
	test_mult.setComp(2, 0, -1);
	test_mult.setComp(0, 1, 1);
	test_mult.setComp(1, 1, 0);
	test_mult.setComp(2, 1, -1);
	
	test_vec.setComponent(0, 1);
	test_vec.setComponent(1, 2);
	test_vec.setComponent(2, 0);
	
	CMyVector res = test_mult * test_vec;
	res.printVec();
	cout << endl;
	test_mult.printMatrix();

	//CMyMatrix res_inv = test_mult.invers();
	//res_inv.printMatrix();

	CMyMatrix test_inv(2, 2);

	test_inv.setComp(0, 0, 2);
	test_inv.setComp(1, 0, 1);
	test_inv.setComp(0, 1, 3);
	test_inv.setComp(1, 1, 4);
	test_inv.printMatrix();

	CMyMatrix res_inv = test_inv.invers();
	res_inv.printMatrix();
	*/

	CMyVector x(2);
	x.setComponent(0, 1);
	x.setComponent(1, 1);
	/*
	CMyVector res = x * (-1);
	res.printVec();
	*/
	newtonverfahren(x, test_aufgabe3);
	return 0;
}