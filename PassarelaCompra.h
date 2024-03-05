#pragma once
#include <iostream>

class PassarelaCompra
{
private:
	std::string data;
	std::string usuari;
	std::string element;
	float preu_pagat = 0;

public:
	PassarelaCompra(std::string d, std::string u, std::string e, float p);

	// getters
	std::string obteData();
	std::string obteUsuari();
	std::string obteElement();
	float obtePreuPagat() const;

	// setter
	void posaDataCompra(std::string dc);

	// retorna un string on hi ha la data i hora actual de registre
	std::string dataCompra();

	void insereix();
};

