#pragma once
#include <iostream>
#include "PassarelaUsuari.h"

class Videoconsola
{
private:
	PassarelaUsuari* usuari = NULL;

	bool sessioiniciada;

	Videoconsola() {
		sessioiniciada = false;
	}

public:
	static Videoconsola& getInstance() {
		static Videoconsola instance;
		return instance;
	}

	bool obteEstatSessio() const;
	void canviaEstatSessio(bool estat);

	void iniciaSessio(PassarelaUsuari usu);
	void tancaSessio();

	PassarelaUsuari* obteUsuari();
};

