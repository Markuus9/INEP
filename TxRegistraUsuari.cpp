#include "TxRegistraUsuari.h"
#include "Videoconsola.h"
#include "PassarelaUsuari.h"

TxRegistraUsuari::TxRegistraUsuari(std::string n, std::string sn, std::string ct, std::string ce, std::string dn) {
	nomU = n;
	sobrenomU = sn;
	contrasenyaU = ct;
	correuElectronicU = ce;
	dataNaixementU = dn;
}

void TxRegistraUsuari::executar() {
	PassarelaUsuari usu = PassarelaUsuari(sobrenomU, nomU, contrasenyaU, correuElectronicU, dataNaixementU);
	usu.insereix();
}
