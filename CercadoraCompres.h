#pragma once
#include <iostream>
#include "PassarelaCompra.h"
#include <vector>

class CercadoraCompres
{
public:
	static std::vector<PassarelaCompra> cercaCompraPerUsuari(std::string sobrenomU);

	static std::vector<PassarelaCompra> cercaCompra(std::string sobrenomU, std::string nomEl);
};

