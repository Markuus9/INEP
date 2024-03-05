#include "TxEsborraUsuari.h"

TxEsborraUsuari::TxEsborraUsuari(std::string ct) {
	contraU = ct;
}

void TxEsborraUsuari::executar() {
	Videoconsola& vc = Videoconsola::getInstance();
	PassarelaUsuari* usu = vc.obteUsuari();

	if (contraU == usu->obteContrasenya()) {
		usu->esborra();
		vc.tancaSessio();
		vc.canviaEstatSessio(false);
	}
	else contrasenyaCorrecte = false;
}
