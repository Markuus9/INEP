#include "PassarelaElemCompra.h"

PassarelaElemCompra::PassarelaElemCompra(std::string n, std::string d, float p, std::string t) {
	nom = n;
	descripcio = d;
	preu = p;
	tipus = t;
}

std::string PassarelaElemCompra::obteNom() {
	return nom;
}

std::string PassarelaElemCompra::obteDescripcio() {
	return descripcio;
}

float PassarelaElemCompra::obtePreu() const {
	return preu;
}

std::string PassarelaElemCompra::obteTipus() {
	return tipus;
}