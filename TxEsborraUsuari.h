#pragma once
#include <iostream>
#include "Transaccio.h"
#include "Videoconsola.h"

class TxEsborraUsuari
{
private:
	std::string contraU;

public:
	// Funcio crear
	TxEsborraUsuari(std::string ct);

	bool contrasenyaCorrecte = true;
	void executar();
};

