#pragma once
#include "Transaccio.h"
#include "PassarelaUsuari.h"
#include <vector>

class TxConsultaUsuari : public Transaccio
{
private:
	
	// nom, sobrenom, correu, dataNaixement i per últim contrasenya
	std::vector<std::string> resultat; 

	PassarelaUsuari* usuari;

public:
	// Funció crear
	TxConsultaUsuari();

	void executar();

	std::vector<std::string> obteResultat();
	PassarelaUsuari* obteUsuari();
};

