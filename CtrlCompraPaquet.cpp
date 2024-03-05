#include "CtrlCompraPaquet.h"

CtrlCompraPaquet::CtrlCompraPaquet(std::string np) {
	Videoconsola& vc = Videoconsola::getInstance();
	usu = vc.obteUsuari();

	nomPaquet = np;
}

std::string CtrlCompraPaquet::obteSobrenomUsuari() {
	return nomPaquet;
}

std::vector<ResultatPaquet> CtrlCompraPaquet::obteConsulta() {
	return consulta;
}

std::string CtrlCompraPaquet::obteData() {
	return data;
}

void CtrlCompraPaquet::consultaPaquet() {
	std::vector<PassarelaElemCompra> paquet = CercadoraElemCompra::cercaElement(nomPaquet);
	if (paquet.size() == 0) paquetExisteix = false;
	else {
		std::vector<PassarelaCompra> compra = CercadoraCompres::cercaCompra(usu->obteSobrenom(), nomPaquet);
		if (compra.size() != 0) compraNova = false;
		else {
			TxConsultarPaquets txCP = TxConsultarPaquets();
			txCP.posaNom(nomPaquet);
			txCP.executar();
			consulta = txCP.obteResultat();
		}
	}
}

void CtrlCompraPaquet::compraPaquet() {
	PassarelaCompra compra = PassarelaCompra(" ", usu->obteSobrenom(), nomPaquet, consulta[0].preu);
	std::string dataCompra = compra.dataCompra();
	compra.posaDataCompra(dataCompra);
	data = dataCompra;

	compra.insereix();
}
