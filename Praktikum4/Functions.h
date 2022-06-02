#pragma once
#include"CKomplex.h"

std::vector<CKomplex> werte_einlesen(const std::string dateiname);
void werte_ausgeben(const std::string dateiname, std::vector<CKomplex> werte, double epsilon);
std::vector<CKomplex> transformation(std::vector<CKomplex> data, bool mode);
double max_dif(std::vector<CKomplex> a, std::vector<CKomplex> b);
void vergleiche_epsilon();