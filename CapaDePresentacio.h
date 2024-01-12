#pragma once
#include <iostream>
#include <string>
#include "Transaccio.h"
#include "TxIniciSessio.h"
using namespace std;

class CapaDePresentacio
{
private:
	CapaDePresentacio();

public:
	static CapaDePresentacio& getInstance() {
		static CapaDePresentacio instance;
		return instance;
	}
};

