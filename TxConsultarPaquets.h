#pragma once
#include "Transaccio.h"
#include "CercadoraElemCompra.h"
#include "CercadoraConte.h"
#include <iostream>
#include <vector>

struct ResultatVideojoc {
	std::string nom;
	std::string descripcio;
	float preu = 0;
};

struct ResultatPaquet {
	std::string nom;
	std::string descripcio;
	float preu = 0;
	float preuJocs = 0;

	std::vector<ResultatVideojoc> videojocs;
};

class TxConsultarPaquets : public Transaccio
{
private:
	std::string nom_paquet = " ";
	std::vector<ResultatPaquet> resultat;

public:
	// Funció crear
	TxConsultarPaquets();

	bool paquetExisteix = true;
	void posaNom(std::string np);

	void executar();

	std::vector<ResultatPaquet> obteResultat();
};

