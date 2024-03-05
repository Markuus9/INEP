#pragma once
#include <iostream>
#include <vector>
#include <pqxx/pqxx>
#include "PassarelaConte.h"

class CercadoraConte
{
public:
	static std::vector<PassarelaConte> cercaPaquetsPerVideojoc(std::string nomV);

	static std::vector<PassarelaConte> cercaVideojocsPerPaquet(std::string nomP);
};

