#pragma once
#include <iostream>

class PassarelaElemCompra
{
private:
	std::string nom;
	std::string descripcio;
	float preu = 0;
	std::string tipus;

public:
	PassarelaElemCompra(std::string n, std::string d, float p, std::string t);

	// getters
	std::string obteNom();
	std::string obteDescripcio();
	float obtePreu() const;
	std::string obteTipus();
};

