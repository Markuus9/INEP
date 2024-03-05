#include "TxIniciSessio.h"
#include "CercadoraUsuari.h"
#include "Videoconsola.h"
#include <iostream>

TxIniciSessio::TxIniciSessio(std::string sn, std::string ct) {
	sobrenom = sn;
	contrasenya = ct;
}

void TxIniciSessio::executar() {
	CercadoraUsuari cercaUsu;
	PassarelaUsuari usu = cercaUsu.cercaUsuari(sobrenom);
	std::string ct = usu.obteContrasenya();

	// usuari existeix
	if (ct != " ") {
		// contrasenya incorrecta
		if (ct != contrasenya) std::cout << "Hi ha hagut un error amb el sobrenom o la contrasenya." << std::endl;
		else {
			Videoconsola& vc = Videoconsola::getInstance();
			vc.iniciaSessio(usu);
			vc.canviaEstatSessio(true);
		}
	}
}