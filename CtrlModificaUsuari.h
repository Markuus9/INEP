#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Videoconsola.h"
#include "PassarelaUsuari.h"
#include "TxConsultaUsuari.h"

class CtrlModificaUsuari
{
private:
	PassarelaUsuari* usuari = NULL;

public:
	CtrlModificaUsuari();

	std::vector<std::string> consultaUsuari();

	bool correuExisteix = false;
	void modificaUsuari(std::string nomU, std::string contraU, std::string correuU, std::string neixU);
};

