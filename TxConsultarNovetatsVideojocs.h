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

	// Mostra tota la informaci� dels videojocs que la seva data de llan�ament sigui m�s gran o igual a "data". 
	// Si "data" �s un string buit, es mostrar� tota la informaci� dels videojocs amb data de llan�ament
	// m�s gran que la data d'avui. La informaci� del videojoc que es mostra �s el nom, descripci�, preu, qualificaci� 
	// per edat, data de llan�ament i temps estimat (si en t�). Si el videojoc est� en algun paquet, es mostra el nom
	// dels paquets en els quals el videojoc est�. La llista de videojoc estar� ordenada descendentment per data.
	void executa(); // override

private:
	std::string data;
};

