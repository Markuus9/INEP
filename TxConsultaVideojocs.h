#pragma once
#include "Transaccio.h"
#include "CercadoraVideojocs.h"
#include "CercadoraElemCompra.h"
#include "CercadoraConte.h"

struct ResultatInfoVideojoc {
	std::string nom;
	std::string descripcio;
	float preu;

	int qEdat;
	std::string genere;
	std::string dLlansament;
	int minsE = 0;

	std::vector<std::string> paquetsOnSurt;
};

class TxConsultaVideojocs : public Transaccio
{
private:
	std::string nomVideojoc = " ";
	int qualificacioEdat = 0;
	std::string dataLlansament = " ";

	std::vector<ResultatInfoVideojoc> resultat;

public:
	// crear
	TxConsultaVideojocs();

	bool videojocExistex = true;
	bool cercaPerData = false;

	void posaNomVideojoc(std::string nv);
	void posaQualificacioEdat(int qe);
	void posaDataLlansament(std::string dl);

	void executar();

	std::vector<ResultatInfoVideojoc> obteResultat();
};

