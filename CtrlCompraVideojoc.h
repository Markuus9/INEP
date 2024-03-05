#pragma once
#include <iostream>
#include <vector>
#include "CercadoraVideojocs.h"
#include "CercadoraCompres.h"
#include "Videoconsola.h"
#include "TxConsultaVideojocs.h"
#include "CercadoraConte.h"

class CtrlCompraVideojoc
{
private:
	std::string nomV;
	ResultatInfoVideojoc consulta;
	PassarelaUsuari* usu = NULL;
	std::string data;

	std::vector<ResultatInfoVideojoc> relacionats;

public:
	CtrlCompraVideojoc(std::string nv);

	bool videojocExisteix = true;
	bool compraNova = true;
	bool videojocApropiat = true;

	// getters
	std::string obteData();
	ResultatInfoVideojoc obteConsulta();
	std::vector<ResultatInfoVideojoc> obteRelacionats();

	void consultaVideojoc();

	void compraVideojoc();

	void videojocsRelacionats();
};

