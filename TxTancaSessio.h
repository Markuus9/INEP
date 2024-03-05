#pragma once
#include "Transaccio.h"

class TxTancaSessio : public Transaccio
{
public:
	// Funció crear
	TxTancaSessio();

	void executar();
};

