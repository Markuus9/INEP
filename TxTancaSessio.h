#pragma once
#include "Transaccio.h"

class TxTancaSessio : public Transaccio
{
public:
	// Funci� crear
	TxTancaSessio();

	void executar();
};

