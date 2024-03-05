#include "TxInfoCompres.h"
#include "Videoconsola.h"
#include "CercadoraCompres.h"
#include "CercadoraElemCompra.h"
#include <vector>

TxInfoCompres::TxInfoCompres() {
	resultat.push_back(0); 
	resultat.push_back(0);
	resultat.push_back(0);
}

void TxInfoCompres::executar() {
	Videoconsola& vc = Videoconsola::getInstance();
	PassarelaUsuari* u = vc.obteUsuari();
	std::string sobrenomU = u->obteSobrenom();

	std::vector<PassarelaCompra> compresU = CercadoraCompres::cercaCompraPerUsuari(sobrenomU);

	float totalPaquets = 0;
	float totalVideojocs = 0;
	float totalEuros = 0;

	for (int i = 0; i < compresU.size(); ++i) {
		PassarelaCompra c = compresU[i];
		
		float preuE = c.obtePreuPagat();
		totalEuros += preuE;

		std::string elem = c.obteElement();
		std::vector<PassarelaElemCompra> compres = CercadoraElemCompra::cercaElement(elem);
		PassarelaElemCompra ec = compres[0];
		if (ec.obteTipus() == "paquet") ++totalPaquets;
		else ++totalVideojocs;
	}
	
	resultat[0] = totalPaquets;
	resultat[1] = totalVideojocs;
	resultat[2] = totalEuros;
}

std::vector<float> TxInfoCompres::obteResultat() {
	return resultat;
}