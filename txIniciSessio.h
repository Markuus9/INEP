#pragma once
#include "transaccio.h"

class txIniciSessio : public transaccio
{
private:
	std::string sobrenom;
	std::string contrasenya;

public: 
	txIniciSessio(std::string sn, std::string ct);

};

