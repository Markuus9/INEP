#pragma once
#include "Transaccio.h"
#include "PassarelaUsuari.h"
#include <vector>

class TxConsultaUsuari : public Transaccio
{
private:
	
	// nom, sobrenom, correu, dataNaixement i per �ltim contrasenya
	std::vector<std::string> resultat; 

	PassarelaUsuari* usuari;

public:
	// Funci� crear
	TxConsultaUsuari();

	void executar();

	std::vector<std::string> obteResultat();
	PassarelaUsuari* obteUsuari();
};

