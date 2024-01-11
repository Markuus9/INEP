#pragma once
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
// #include "Transaccio.h"
#include "TxConsultarVideojocCompactat.h"
#include "Videoconsola.h"
using namespace std;

class TxConsultarNovetatsVideojocs //:  public Transaccio
{

public:
	// constructora
	TxConsultarNovetatsVideojocs(std::string dataConsulta);

	// Mostra tota la informació dels videojocs que la seva data de llançament sigui més gran o igual a "data". 
	// Si "data" és un string buit, es mostrarà tota la informació dels videojocs amb data de llançament
	// més gran que la data d'avui. La informació del videojoc que es mostra és el nom, descripció, preu, qualificació 
	// per edat, data de llançament i temps estimat (si en té). Si el videojoc està en algun paquet, es mostra el nom
	// dels paquets en els quals el videojoc està. La llista de videojoc estarà ordenada descendentment per data.
	void executa(); // override

private:
	std::string data;
};

