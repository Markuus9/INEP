#pragma once
#include "Transaccio.h"
#include <vector>

class TxInfoCompres : public Transaccio
{
private:
	std::vector<float> resultat;

public:
	TxInfoCompres(); // Crear

	void executar();

	std::vector<float> obteResultat();
};

