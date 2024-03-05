#include "TxConsultarPaquets.h"
#include "CercadoraPreuJocs.h"

TxConsultarPaquets::TxConsultarPaquets() {

}

void TxConsultarPaquets::posaNom(std::string np) {
	nom_paquet = np;
}

void TxConsultarPaquets::executar() {
	std::vector<PassarelaElemCompra> resultatElemCompra;
	if (nom_paquet == " ") resultatElemCompra = CercadoraElemCompra::cercaTotsPaquets();
	else resultatElemCompra = CercadoraElemCompra::cercaElement(nom_paquet);

	if (nom_paquet != " " and resultatElemCompra.size() == 0) paquetExisteix = false;
	else {
		for (unsigned int i = 0; i < resultatElemCompra.size(); ++i) {
			ResultatPaquet paquet;
			paquet.nom = resultatElemCompra[i].obteNom();
			paquet.descripcio = resultatElemCompra[i].obteDescripcio();
			paquet.preu = resultatElemCompra[i].obtePreu();

			PassarelaPreuJocs pj = CercadoraPreuJocs::cercaPreuJocs(paquet.nom);
			paquet.preuJocs = pj.obtePreuJocs();

			std::vector<PassarelaConte> conte = CercadoraConte::cercaVideojocsPerPaquet(paquet.nom);

			for (unsigned int j = 0; j < conte.size(); ++j) {
				ResultatVideojoc videojoc;

				std::string nomV = conte[j].obteNomVideojoc();
				std::vector<PassarelaElemCompra> resultatVd = CercadoraElemCompra::cercaElement(nomV);
				videojoc.nom = resultatVd[0].obteNom();
				videojoc.descripcio = resultatVd[0].obteDescripcio();
				videojoc.preu = resultatVd[0].obtePreu();

				paquet.videojocs.push_back(videojoc);
			}

			resultat.push_back(paquet);
		}
	}
}

std::vector<ResultatPaquet> TxConsultarPaquets::obteResultat() {
	return resultat;
}