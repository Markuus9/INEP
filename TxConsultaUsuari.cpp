#include "TxConsultaUsuari.h"
#include "Videoconsola.h"

TxConsultaUsuari::TxConsultaUsuari() {
	usuari = NULL;
}

void TxConsultaUsuari::executar() {
	Videoconsola& vc = Videoconsola::getInstance();
	usuari = vc.obteUsuari();
	resultat.push_back(usuari->obteNom());
	resultat.push_back(usuari->obteSobrenom());
	resultat.push_back(usuari->obteCorreuElectronic());
	resultat.push_back(usuari->obteDataNaixement());
	resultat.push_back(usuari->obteContrasenya());
}

std::vector<std::string> TxConsultaUsuari::obteResultat() {
	return resultat;
}

PassarelaUsuari* TxConsultaUsuari::obteUsuari() {
	return usuari;
}