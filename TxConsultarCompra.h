#pragma once
#include <iostream>
#include <vector>
#include "Transaccio.h"
#include "Videoconsola.h"
#include "CercadoraCompres.h"
#include "CercadoraElemCompra.h"
#include "CercadoraConte.h"

struct InfoVideojoc {
	std::string nom;
	std::string descripcio;
};

struct InfoElemCompra {
	std::string data;
	std::string nom;
	std::string descripcio;
	std::string tipus;
	float preu = 0;

	std::vector<InfoVideojoc> videojocs;
};

class TxConsultarCompra : public Transaccio
{
private:
	std::vector<InfoElemCompra> resultat;
	float totalEurosGastats = 0;

public:
	TxConsultarCompra();

	float obteTotalEurosGastats() const;

	void executar();

	std::vector<InfoElemCompra> obteResultat();
};

