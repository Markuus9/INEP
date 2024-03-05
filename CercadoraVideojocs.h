#pragma once
#include <iostream>
#include <vector>
#include "PassarelaVideojoc.h"

class CercadoraVideojocs
{
public:
	static std::vector<PassarelaVideojoc> cercaVideojocPerNom(std::string nomV);

	static std::vector<PassarelaVideojoc> cercaTotsVideojocs();

	static std::vector<PassarelaVideojoc> cercaVideojocsPerEdat(int edat);

	static std::vector<PassarelaVideojoc> cercaVideojocsPerDataLlansament(std::string dataL);

};

