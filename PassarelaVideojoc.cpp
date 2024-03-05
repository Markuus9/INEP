#include "PassarelaVideojoc.h"

PassarelaVideojoc::PassarelaVideojoc(std::string n, int qE, std::string dl, int mE, std::string gen) {
	nom = n;
	qualificacio_edat = qE;
	data_llansament = dl;
	mins_estimat = mE;
	genere = gen;
}

std::string PassarelaVideojoc::obteNom() const {
	return nom;
}

int PassarelaVideojoc::obteQualificacioEdat() const {
	return qualificacio_edat;
}

std::string PassarelaVideojoc::obteDataLlansament() const {
	return data_llansament;
}

int PassarelaVideojoc::obteMinsEstimat() const {
	return mins_estimat;
}

std::string PassarelaVideojoc::obteGenere() const {
	return genere;
}