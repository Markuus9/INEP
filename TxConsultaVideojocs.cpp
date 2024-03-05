#include "TxConsultaVideojocs.h"

TxConsultaVideojocs::TxConsultaVideojocs() {

}

void TxConsultaVideojocs::posaNomVideojoc(std::string nv) {
	nomVideojoc = nv;
}

void TxConsultaVideojocs::posaQualificacioEdat(int qe) {
	qualificacioEdat = qe;
}

void TxConsultaVideojocs::posaDataLlansament(std::string dl) {
	dataLlansament = dl;
}

void TxConsultaVideojocs::executar() {
	std::vector<PassarelaVideojoc> resultatVideojocs;
	if (nomVideojoc != " ") resultatVideojocs = CercadoraVideojocs::cercaVideojocPerNom(nomVideojoc);
	else if (qualificacioEdat != 0) resultatVideojocs = CercadoraVideojocs::cercaVideojocsPerEdat(qualificacioEdat);
	else if (cercaPerData) resultatVideojocs = CercadoraVideojocs::cercaVideojocsPerDataLlansament(dataLlansament);
	else resultatVideojocs = CercadoraVideojocs::cercaTotsVideojocs();

	if (nomVideojoc != " " and resultatVideojocs.size() == 0) videojocExistex = false;
	else {
		for (unsigned int i = 0; i < resultatVideojocs.size(); ++i) {
			ResultatInfoVideojoc rV;
			rV.nom = resultatVideojocs[i].obteNom();
			rV.qEdat = resultatVideojocs[i].obteQualificacioEdat();
			rV.genere = resultatVideojocs[i].obteGenere();
			rV.dLlansament = resultatVideojocs[i].obteDataLlansament();
			rV.minsE = resultatVideojocs[i].obteMinsEstimat();

			std::vector<PassarelaElemCompra> elemCompra = CercadoraElemCompra::cercaElement(rV.nom);
			rV.descripcio = elemCompra[0].obteDescripcio();
			rV.preu = elemCompra[0].obtePreu();

			std::vector<PassarelaConte> conte = CercadoraConte::cercaPaquetsPerVideojoc(rV.nom);
			for (unsigned int j = 0; j < conte.size(); ++j) {
				rV.paquetsOnSurt.push_back(conte[j].obteNomPaquet());
			}
			
			resultat.push_back(rV);
		}
	}
}

std::vector<ResultatInfoVideojoc> TxConsultaVideojocs::obteResultat() {
	return resultat;
}