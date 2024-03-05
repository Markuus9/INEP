#pragma once
#include "Transaccio.h"
#include <iostream>

class TxRegistraUsuari : public Transaccio
{
private:
	// atributs
	std::string nomU;
	std::string sobrenomU;
	std::string contrasenyaU;
	std::string correuElectronicU;
	std::string dataNaixementU;

public:
	// Funció crear
	TxRegistraUsuari(std::string n, std::string sn, std::string ct, std::string ce, std::string dn);

	void executar();
};

