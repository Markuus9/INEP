#pragma once
#include "PassarelaElemCompra.h"
#include <pqxx/pqxx>
#include <vector>

class CercadoraElemCompra
{
public:
	static std::vector<PassarelaElemCompra> cercaElement(std::string nomElem);

	static std::vector<PassarelaElemCompra> cercaTotsElements();

	static std::vector<PassarelaElemCompra> cercaTotsPaquets();
};

