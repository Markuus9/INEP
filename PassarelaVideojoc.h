#pragma once
#include <iostream>
#include "PassarelaElemCompra.h"

class PassarelaVideojoc
{
private:
	std::string nom;
	int qualificacio_edat = 0;
	std::string data_llansament;
	int mins_estimat = 0;
	std::string genere;

public:
	PassarelaVideojoc(std::string n, int qE, std::string dl, int mE, std::string gen);

	// getter
	std::string obteNom() const;
	int obteQualificacioEdat() const;
	std::string obteDataLlansament() const;
	int obteMinsEstimat() const;
	std::string obteGenere() const;
};

