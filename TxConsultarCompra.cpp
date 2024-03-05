#include "TxConsultarCompra.h"

TxConsultarCompra::TxConsultarCompra() {

}

float TxConsultarCompra::obteTotalEurosGastats() const {
	return totalEurosGastats;
}

void TxConsultarCompra::executar() {
	Videoconsola& vc = Videoconsola::getInstance();
	PassarelaUsuari* usu = vc.obteUsuari();

	std::vector<PassarelaCompra> compres = CercadoraCompres::cercaCompraPerUsuari(usu->obteSobrenom());
	for (unsigned int i = 0; i < compres.size(); ++i) {
		InfoElemCompra iEC;
		iEC.data = compres[i].obteData();
		iEC.nom = compres[i].obteElement();
		iEC.preu = compres[i].obtePreuPagat();
		totalEurosGastats += iEC.preu;

		std::vector<PassarelaElemCompra> elements = CercadoraElemCompra::cercaElement(iEC.nom);
		iEC.tipus = elements[0].obteTipus();
		iEC.descripcio = elements[0].obteDescripcio();

		if (iEC.tipus == "paquet") {
			std::vector<PassarelaConte> contingut = CercadoraConte::cercaVideojocsPerPaquet(iEC.nom);
			for (unsigned int j = 0; j < contingut.size(); ++j) {
				std::string nVideojoc = contingut[j].obteNomVideojoc();
				std::vector<PassarelaElemCompra> elementV = CercadoraElemCompra::cercaElement(nVideojoc);

				InfoVideojoc iVd;
				iVd.nom = nVideojoc;
				iVd.descripcio = elementV[0].obteDescripcio();

				iEC.videojocs.push_back(iVd);
			}

		}

		resultat.push_back(iEC);
	}
}

std::vector<InfoElemCompra> TxConsultarCompra::obteResultat() {
	return resultat;
}
