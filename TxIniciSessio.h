#pragma once
#include "Transaccio.h"

class TxIniciSessio : public Transaccio
{
private:
	// atributs
	std::string sobrenom;
	std::string contrasenya;

public: 
	// Funció crear
	TxIniciSessio(std::string sn, std::string ct);

	void executar();
};

