#pragma once
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
// #include "Transaccio.h"
#include "Videoconsola.h"
using namespace std;

class TxConsultarPaquets // : public Transaccio
{

public:
	// constructora
	TxConsultarPaquets();

	// Mostra el nom, descripci�, preu de tots els paquets de la base de dades. Per a cada paquet tamb� es mostra
	// l'estalvi (en euros) en relaci� amb comprar els videojocs que cont� per separat.
	void executa(); // override
};

