#pragma once
#include "Transaccio.h"

class TxIniciSessio : public Transaccio
{
private:
	std::string sobrenom;
	std::string contrasenya;

public: 
	TxIniciSessio(std::string sn, std::string ct);

};

