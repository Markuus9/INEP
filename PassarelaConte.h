#pragma once
#include <iostream>

class PassarelaConte
{
private:
	std::string nPaquet;
	std::string nVideojoc;

public:
	PassarelaConte(std::string nV, std::string nP);

	std::string obteNomPaquet();
	std::string obteNomVideojoc();
};

