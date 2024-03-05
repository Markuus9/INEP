#include "Videoconsola.h"

bool Videoconsola::obteEstatSessio() const {
	return sessioiniciada;
}

void Videoconsola::canviaEstatSessio(bool estat) {
	sessioiniciada = estat;
}

void Videoconsola::iniciaSessio(PassarelaUsuari usu) {
	usuari = new PassarelaUsuari;
	*usuari = usu;
}

void Videoconsola::tancaSessio() {
	delete usuari;
}

PassarelaUsuari* Videoconsola::obteUsuari() {
	return usuari;
}