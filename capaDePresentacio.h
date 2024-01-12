#pragma once
#include <iostream>
#include <string>
#include "transaccio.h"
#include "txIniciSessio.h"
using namespace std;

class capaDePresentacio
{
private:
	capaDePresentacio();

public:
	static capaDePresentacio& getInstance() {
		static capaDePresentacio instance;
		return instance;
	}

	void iniciSessio();
};

