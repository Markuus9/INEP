#pragma once
#include <iostream>

class PassarelaPreuJocs
{
private:
	std::string nom_paquet;
	float preu_jocs;

public:
	PassarelaPreuJocs(std::string np, float pj);

	// getters
	std::string obteNomPaquet();
	float obtePreuJocs();
};

