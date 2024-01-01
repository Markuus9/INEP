#include "Videoconsola.h"

Videoconsola::Usuari Videoconsola::obteUsuari() {
	return usu;
}

bool Videoconsola::obteEstatSessio() {
	return sessioiniciada;
}

std::string Videoconsola::obteNomUsuari() {
	return usu.nom;
}

std::string Videoconsola::obteSobrenomUsuari() {
	return usu.sobrenom;
}

std::string Videoconsola::obteContrasenyaUsuari() {
	return usu.contrasenya;
}

std::string Videoconsola::obteCorreuElectronicUsuari() {
	return usu.correuElectronic;
}

std::string Videoconsola::obteDataNaixementUsuari() {
	return usu.dataNaixement;
}


void Videoconsola::canviaEstatSessio(bool estat) {
	sessioiniciada = estat;
}

void Videoconsola::modificarNomUsuari(std::string n) {
	usu.nom = n;
}
void Videoconsola::modificarSobrenomUsuari(std::string sn) {
	usu.sobrenom = sn;
}
void Videoconsola::modificarContrasenyaUsuari(std::string ct) {
	usu.contrasenya = ct;
}
void Videoconsola::modificarCorreuElectronicUsuari(std::string ce) {
	usu.correuElectronic = ce;
}
void Videoconsola::modificarDataNaixementUsuari(std::string dn) {
	usu.dataNaixement = dn;
}