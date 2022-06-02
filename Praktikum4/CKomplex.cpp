#pragma once
#include"CKomplex.h"


//Constructors
CKomplex::CKomplex() {}
CKomplex::CKomplex(double a, double b) {
	real = a;
	ima = b;
}
CKomplex::CKomplex(double phi) {
		real = cos(phi);
		ima = sin(phi);
}
CKomplex::CKomplex(const CKomplex& x) {
	this->real = x.real;
	this->ima = x.ima;
}

//Getter
double CKomplex::re() { return real; }
double CKomplex::im() { return ima; }

//Operators
CKomplex CKomplex::operator+(CKomplex b){
	CKomplex result(real + b.real, ima + b.ima);
	return result;
}
CKomplex CKomplex::operator-(CKomplex b) {
	CKomplex result(this->real - b.real, this->ima - b.ima);
	return result;
}
CKomplex CKomplex::operator*(double lambda){
	CKomplex result(this->real * lambda, this->ima * lambda);
	return result;
}
CKomplex CKomplex::operator*(CKomplex x){
	CKomplex result((this->real * x.real) + (-1 * (this->ima * x.ima)), (this->real * x.ima) + (this->ima * x.real));
	return result;
}
CKomplex CKomplex::operator=(CKomplex x){
	this->real = x.real;
	this->ima = x.ima;
	return *this;
}
CKomplex CKomplex::operator+=(CKomplex x) {
	this->real += x.real;
	this->ima += x.ima;
	return *this;
}
CKomplex operator*(double lambda, CKomplex x) {
	return x * lambda;
}

//Helper-Functions
//Gibt den Betrag der komplexen Zahl zurück
double CKomplex::abs(){
	return sqrt((this->real * this->real) + (this->ima * this->ima));
}

//Print-functions
void CKomplex::printKomp(){
	//Realteil
	if (this->real != 0) {
		std::cout << this->real;
	}

	//Imaginärteil
	if (this->ima < 0){
		std::cout << "-" << this->ima << "j";
		return;
	}
	else if (this->ima == 0){
		return;
	}
	else if (this->ima > 0) {
		std::cout << "+" << this->ima << "j";
		return;
	}
}
std::string CKomplex::to_string(){
	//Realteil
	std::string out = "";
	if (this->real != 0) {
		out+= std::to_string(this->real);
	}

	//Imaginärteil
	if (this->ima < 0) {
		((out += "-") += std::to_string(this->ima)) += "j";
		return out;
	}
	else if (this->ima == 0) {
		return out;
	}
	else if (this->ima > 0) {
		((out += "+") += std::to_string(this->ima)) += "j";
		return out;
	}
	return out;
}
