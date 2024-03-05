#pragma once
#include "Transaccio.h"
#include "CercadoraElemCompra.h"
#include "CercadoraCompres.h"
#include "Videoconsola.h"
#include "TxConsultarPaquets.h"
#include <vector>

class CtrlCompraPaquet
{
private:
	std::string nomPaquet;
	PassarelaUsuari* usu = NULL;
	std::string data;
	float preu = 0;

	std::vector<ResultatPaquet> consulta;

public:
	// crear Ctrl
	CtrlCompraPaquet(std::string np);

	// getters
	std::string obteSobrenomUsuari();
	std::vector<ResultatPaquet> obteConsulta();
	std::string obteData();

	bool paquetExisteix = true;
	bool compraNova = true;

	void consultaPaquet();
	void compraPaquet();
};

