#include "CMyVector.h"


	//Constructors
	CMyVector::CMyVector(int i) {
		dim = i;
		setDim(i);
	}

	CMyVector::CMyVector(const CMyVector& x) {
		dim = x.dim;
		setDim(dim);
		for (int i = 0; i < x.dim; i++) {
			setComponent(i, x.vec.at(i));
		}
	}


	//Getter and Setter
	void CMyVector::setDim(int i) {
		dim = i;
		vec.resize(i, 0);
	}

	int CMyVector::getDim() {
		return dim;
	}

	double CMyVector::getComponent(int i) {
		return vec[i];
	};

	void CMyVector::setComponent(int i, double comp) {
		vec[i] = comp;
	}

	double CMyVector::getLength() {
		double sum = 0;
		for (int i = 0; i < vec.size(); i++) {
			sum += pow(vec[i], 2);
		}

		if (sum < 0) { sum *= -1; }

		return sqrt(sum);
	}


	//Operators
	CMyVector CMyVector::operator+(CMyVector b) {
		if (this->getDim() == b.getDim()) {
			CMyVector c(b.getDim());
			for (int i = 0; i < b.getDim(); i++) {
				c.setComponent(i, (this->getComponent(i) + b.getComponent(i)));
			}
			return c;
		}
	}


	CMyVector CMyVector::operator*(double lambda) {
		CMyVector out(this->getDim());
		for (int i = 0; i < this->getDim(); i++) {
			out.setComponent(i, (this->getComponent(i) * lambda));
		}
		return out;
	}

	CMyVector CMyVector::operator*(CMyVector x) {
		if (x.getDim() == this->getDim()) {
			CMyVector out(x.getDim());
			for (int i = 0; i < x.getDim(); i++) {
				out.setComponent(i, x.getComponent(i) * this->getComponent(i));
			}
			return out;
		}
	}

	CMyVector CMyVector::operator=(CMyVector x) {
		setDim(x.getDim());
		for (int i = 0; i < x.getDim(); i++) {
			setComponent(i, x.getComponent(i));
		}
		return *this;
	}


	//Print-functions
	void CMyVector::printVec() {
		std::cout << "( ";
		for (int i = 0; i < getDim(); i++) {
			std::cout << getComponent(i);
			if (i != getDim() - 1)
				std::cout << "; ";
		}
		std::cout << " )";
	}

	std::string CMyVector::vecToString() {
		std::string out;
		out += "( ";
		for (int i = 0; i < getDim(); i++) {
			out += std::to_string(getComponent(i));
			if (i != getDim() - 1)
				out += "; ";
		}
		out += " )";

		return out;
	}

	
	CMyVector operator*(double lambda, CMyVector x) {
		return x * lambda;
	};
