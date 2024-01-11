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

	// Mostra el nom, descripció, preu de tots els paquets de la base de dades. Per a cada paquet també es mostra
	// l'estalvi (en euros) en relació amb comprar els videojocs que conté per separat.
	void executa(); // override
};

