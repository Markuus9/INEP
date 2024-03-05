#include "CtrlModificaUsuari.h"

CtrlModificaUsuari::CtrlModificaUsuari() {
	Videoconsola& vc = Videoconsola::getInstance();
	usuari = vc.obteUsuari();
}

std::vector<std::string> CtrlModificaUsuari::consultaUsuari() {
	TxConsultaUsuari TxCU = TxConsultaUsuari();
	TxCU.executar();
	std::vector<std::string> resultatCU = TxCU.obteResultat();
	return resultatCU;
}

void CtrlModificaUsuari::modificaUsuari(std::string nomU, std::string contraU, std::string correuU, std::string neixU) {
	correuExisteix = usuari->correuExisteix(correuU);
	if (not correuExisteix) {
		if (nomU.length() != 0) usuari->posaNom(nomU);
		if (contraU.length() != 0) usuari->posaContrasenya(contraU);
		if (correuU.length() != 0) usuari->posaCorreuElectronic(correuU);
		if (neixU.length() != 0) usuari->posaDataNaixement(neixU);

		usuari->modifica();
	}
}