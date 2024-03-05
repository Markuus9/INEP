#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Transaccio.h"
#include "TxIniciSessio.h"
#include "TxTancaSessio.h"
#include "TxRegistraUsuari.h"
#include "TxConsultaUsuari.h"
#include "TxInfoCompres.h"
#include "CtrlModificaUsuari.h"
#include "TxEsborraUsuari.h"
#include "TxConsultarPaquets.h"
#include "TxConsultaVideojocs.h"
#include "TxConsultarCompra.h"
#include "CtrlCompraVideojoc.h"
#include "CtrlCompraPaquet.h"

using namespace std;

class CapaDePresentacio
{	
public:
	static CapaDePresentacio& getInstance() {
		static CapaDePresentacio instance;
		return instance;
	}

	void iniciSessio();
	void tancaSessio();

	void registrarUsuari();
	void consultaUsuari();
	void modificaUsuari();
	std::string confirmarContrasenya();
	void esborraUsuari(bool& gestioUsuari);

	void comprarVideojoc();
	void comprarPaquet();
	void consultarCompres();

	void consultarVideojoc();
	void consultarVideojocs();
	void consultarVideojocsPerEdat();
	void consultarNovetatsVideojocs();
	void consultarPaquet();
	void consultarPaquets();
};

