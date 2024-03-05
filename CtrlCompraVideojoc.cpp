#include "CtrlCompraVideojoc.h"

CtrlCompraVideojoc::CtrlCompraVideojoc(std::string nv) {
	Videoconsola& vc = Videoconsola::getInstance();
	usu = vc.obteUsuari();

	nomV = nv;
}

void CtrlCompraVideojoc::consultaVideojoc() {
	std::vector<PassarelaVideojoc> videojoc = CercadoraVideojocs::cercaVideojocPerNom(nomV);
	if (videojoc.size() == 0) videojocExisteix = false;
	else {
		std::vector<PassarelaCompra> compra = CercadoraCompres::cercaCompra(usu->obteSobrenom(), nomV);
		if (compra.size() != 0) compraNova = false;
		else {
			int edatUsu = usu->obteEdat();
			if (edatUsu < videojoc[0].obteQualificacioEdat()) videojocApropiat = false;
			else {
				TxConsultaVideojocs txCV = TxConsultaVideojocs();
				txCV.posaNomVideojoc(nomV);
				txCV.executar();

				std::vector<ResultatInfoVideojoc> consultes = txCV.obteResultat();
				consulta = consultes[0];
			}
		}
	}
}

ResultatInfoVideojoc CtrlCompraVideojoc::obteConsulta() {
	return consulta;
}

std::vector<ResultatInfoVideojoc> CtrlCompraVideojoc::obteRelacionats() {
	return relacionats;
}

std::string CtrlCompraVideojoc::obteData() {
	return data;
}

void CtrlCompraVideojoc::compraVideojoc() {
	PassarelaCompra compra = PassarelaCompra(" ", usu->obteSobrenom(), nomV, consulta.preu);
	std::string dataCompra = compra.dataCompra();
	compra.posaDataCompra(dataCompra);
	data = dataCompra;

	compra.insereix();
}

void CtrlCompraVideojoc::videojocsRelacionats() {
	for (unsigned int i = 0; i < consulta.paquetsOnSurt.size(); ++i) {
		std::vector<PassarelaConte> conte = CercadoraConte::cercaVideojocsPerPaquet(consulta.paquetsOnSurt[i]);

		std::vector<ResultatInfoVideojoc> resultat;
		for (unsigned int j = 0; j < conte.size(); ++j) {
			TxConsultaVideojocs txCV = TxConsultaVideojocs();
			txCV.posaNomVideojoc(conte[j].obteNomVideojoc());
			txCV.executar();

			 resultat = txCV.obteResultat();
			 relacionats.push_back(resultat[0]);
		}
	}
}
