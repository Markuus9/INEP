#pragma once
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
#include "Videoconsola.h"
using namespace std;

class TxComprarPaquet //:  public Transaccio
{

public:
	// constructora
	TxComprarPaquet(std::string npaquet);


	// Si l'usuari loggejat confirma la compra s'enregistra a la base de dades la compra del paquetvideojocs de nom n
	// per part de l'usuari amb data corresponent a la data i hora en la que es fa la compra.
	// Una vegada enregistrada la compra, es mostra la data corresponent a la data i hora en la que s'ha realitzat la compra.
	void executa (std::string n); // override

private:
	std::string n;
};

