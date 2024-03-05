#include "CapaDePresentacio.h"
#include <conio.h>

void CapaDePresentacio::iniciSessio()
{
	std::cout << "** Inici sessio **" << std::endl;
	std::string sn, ct;
	std::cout << "Sobrenom: ";
	std::getline(cin, sn);
	std::cout << "Contrasenya: ";
	std::getline(cin, ct);
	TxIniciSessio iniciSessio = TxIniciSessio(sn, ct);
	iniciSessio.executar();
}

void CapaDePresentacio::tancaSessio() {
	std::cout << "** Tancar sessio **" << std::endl;
	std::cout << "Vols tancar la sessio (S/N): " << std::endl;
	std::string resposta;
	bool sortir = false;
	while (not sortir) {
		std::cin >> resposta;
		if (resposta == "S" or resposta == "N") sortir = true;
	}
	std::cin.ignore();
	if (resposta == "S") {
		TxTancaSessio tancaSessio = TxTancaSessio();
		tancaSessio.executar();
		std::cout << "Sessio tancada correctament! " << std::endl;
	}
}

void CapaDePresentacio::registrarUsuari() {
	std::cout << "** Registrar usuari **" << std::endl;
	std::cout << "Omplir la informacio que es demana..." << endl;
	std::string n, sn, ct, ce, dn;
	std::cout << "Nom complet: ";
	std::getline(cin, n);
	std::cout << "Sobrenom: ";
	std::getline(cin, sn);
	std::cout << "Contrasenya: ";
	std::getline(cin, ct);
	std::cout << "Correu electronic: ";
	std::getline(cin, ce);
	std::cout << "Data naixement (AAAA-MM-DD): ";
	std::getline(cin, dn);
	TxRegistraUsuari TxRU = TxRegistraUsuari(n, sn, ct, ce, dn);
	TxRU.executar();
}

void CapaDePresentacio::consultaUsuari() {
	TxConsultaUsuari TxCU = TxConsultaUsuari();
	TxCU.executar();
	std::vector<std::string> resultatCU = TxCU.obteResultat();
	std::cout << "Nom complet: " << resultatCU[0] << std::endl;
	std::cout << "Sobrenom: " << resultatCU[1] << std::endl;
	std::cout << "Correu electronic: " << resultatCU[2] << std::endl;
	std::cout << "Data naixement (AAAA-MM-DD): " << resultatCU[3] << std::endl;

	TxInfoCompres TxIC = TxInfoCompres();
	TxIC.executar();
	std::vector<float> resultatIC = TxIC.obteResultat();

	float videojocs = resultatIC[1];
	float paquets = resultatIC[0];
	float euros = resultatIC[2];

	std::cout << videojocs << " videojoc";
	if (videojocs != 1) std::cout << "s";
	std::cout << " comprat";
	if (videojocs != 1) std::cout << "s";

	std::cout << endl << paquets << " paquet";
	if (paquets != 1) std::cout << "s";
	std::cout << " de videojocs comprat";
	if (paquets != 1) std::cout << "s";

	std::cout << endl << euros << " euros gastats en total" << endl;
}

void CapaDePresentacio::modificaUsuari() {
	CtrlModificaUsuari ctrlMU = CtrlModificaUsuari();
	std::vector<std::string> consulta = ctrlMU.consultaUsuari();
	std::cout << "Nom complet: " << consulta[0] << std::endl;
	std::cout << "Sobrenom: " << consulta[1] << std::endl;
	std::cout << "Correu electronic: " << consulta[2] << std::endl;
	std::cout << "Data naixement (AAAA-MM-DD): " << consulta[3] << std::endl;

	std::cout << "Omplir la informacio que es vol modificar..." << std::endl;
	std::string nomU, contraU, correuU, neixU;
	std::cout << "Nom complet: ";
	std::getline(std::cin, nomU);
	std::cout << "Contrasenya: ";
	std::getline(std::cin, contraU);
	std::cout << "Correu electronic: ";
	std::getline(std::cin, correuU);
	std::cout << "Data de naixement (AAAA-MM-DD): ";
	std::getline(std::cin, neixU);

	ctrlMU.modificaUsuari(nomU, contraU, correuU, neixU);
	if (ctrlMU.correuExisteix) std::cout << "El correu electronic ja existeix" << std::endl;
	else {
		std::cout << "** Dades usuari modificades **" << std::endl;
		std::vector<std::string> consulta = ctrlMU.consultaUsuari();
		std::cout << "Nom complet: " << consulta[0] << std::endl;
		std::cout << "Sobrenom: " << consulta[1] << std::endl;
		std::cout << "Correu electronic: " << consulta[2] << std::endl;
		std::cout << "Data naixement (AAAA-MM-DD): " << consulta[3] << std::endl;
	}
}

std::string CapaDePresentacio::confirmarContrasenya() {
	std::string contrasenya;

	char caracter = _getch();
	while (caracter != 13)
	{
		contrasenya += caracter;
		cout << '*';
		caracter = _getch();
	}
	std::cout << endl;
	return contrasenya;
}

void CapaDePresentacio::esborraUsuari(bool& gestioUsuari) {
	std::cout << "** Esborrar usuari **" << std::endl;
	std::cout << "Per confirmar l'esborrat, s'ha d'entrar la contrasenya..." << std::endl;
	std::cout << "Contrasenya: ";
	std::string ct = confirmarContrasenya();

	TxEsborraUsuari TxEU = TxEsborraUsuari(ct);
	TxEU.executar();
	if (TxEU.contrasenyaCorrecte) {
		std::cout << "Usuari esborrat correctament!" << std::endl;
		gestioUsuari = false;
	}
	else std::cout << "La contrasenya no es correcte, l'usuari no s'ha esborrat." << std::endl;
}

void CapaDePresentacio::comprarVideojoc() {
	std::cout << "** Comprar videojoc **" << endl;
	std::cout << "Nom videojoc: ";
	std::string nom;
	getline(cin, nom);

	CtrlCompraVideojoc cv = CtrlCompraVideojoc(nom);
	cv.consultaVideojoc();

	if (cv.videojocExisteix) {
		if (cv.compraNova) {
			if (cv.videojocApropiat) {
				ResultatInfoVideojoc consulta = cv.obteConsulta();
				cout << "Informacio videojoc..." << endl;
				cout << "Nom videojoc: " << consulta.nom << endl;
				cout << "Descripcio: " << consulta.descripcio << endl;
				cout << "Qualificacio edat: " << consulta.qEdat << endl;
				cout << "Genere: " << consulta.genere << endl;
				cout << "Data llansamet: " << consulta.dLlansament << endl;
				cout << "Preu: " << consulta.preu << " euros" << endl;

				cout << "Vols continuar amb la compra? (S/N): ";
				char resposta;
				bool sortir = false;
				while (not sortir) {
					cin >> resposta;
					if (resposta == 'S' or resposta == 'N') {
						sortir = true;
					}
				}
				cin.ignore(); // Per si en el futur es fa servir getline

				if (resposta == 'S') {
					cv.compraVideojoc();
					cout << "Compra registrada: " << cv.obteData() << endl;

					cv.videojocsRelacionats();
					std::vector<ResultatInfoVideojoc> relacionats = cv.obteRelacionats();
					if (0 < relacionats.size()) {
						cout << "Jocs relacionats: " << endl;
						for (unsigned int j = 0; j < relacionats.size(); ++j) {
							if (relacionats[j].nom != nom) {
								std::cout << "- " << relacionats[j].nom << "; ";
								std::cout << relacionats[j].descripcio << "; ";
								std::cout << relacionats[j].preu << " euros" << endl;
							}
						}
					}
				}
				else std::cout << "No s'ha efectuat la compra." << endl;
			}
			else cout << "El videojoc no es adequat per l'edat de l'usuari." << endl;
		}
		else cout << "Ja has comprat aquest joc anteriorment." << endl;
	}
	else cout << "El videojoc no existeix" << endl;
}

void CapaDePresentacio::comprarPaquet() {
	std::cout << "** Comprar paquet **" << endl;
	std::cout << "Nom paquet: ";
	std::string nom;
	getline(cin, nom);
	CtrlCompraPaquet cCP = CtrlCompraPaquet(nom);
	cCP.consultaPaquet();
	if (cCP.paquetExisteix) {
		if (cCP.compraNova) {
			vector<ResultatPaquet> consultaP = cCP.obteConsulta();
			cout << "Informacio paquet..." << endl;
			cout << "Nom paquet: " << consultaP[0].nom << endl;
			cout << "Descripcio: " << consultaP[0].descripcio << endl;
			cout << "Preu: " << consultaP[0].preu << " euros (estalvi de ";
			cout << consultaP[0].preuJocs - consultaP[0].preu << " euros)" << endl;

			std::cout << "Jocs inclosos:" << endl;
			for (unsigned int i = 0; i < consultaP[0].videojocs.size(); ++i) {
				std::cout << "- " << consultaP[0].videojocs[i].nom << "; ";
				std::cout << consultaP[0].videojocs[i].descripcio << "; ";
				std::cout << consultaP[0].videojocs[i].preu << " euros" << endl;
			}

			cout << "Vols continuar amb la compra? (S/N): ";
			char resposta;
			bool sortir = false;
			while (not sortir) {
				cin >> resposta;
				if (resposta == 'S' or resposta == 'N') {
					sortir = true;
				}
			}
			cin.ignore(); // Per si en el futur es fa servir getline

			if (resposta == 'S') {
				cCP.compraPaquet();
				cout << "Compra registrada: " << cCP.obteData() << endl;
			}
			else std::cout << "No s'ha efectuat la compra." << endl;
		}
		else std::cout << "Ja has comprat aquest paquet de videojocs anteriorment." << endl;
	}
	else std::cout << "El paquet no existeix." << endl;
}

void CapaDePresentacio::consultarCompres() {
	std::cout << "** Consultar compres **" << endl;
	TxConsultarCompra txCC = TxConsultarCompra();
	txCC.executar();
	std::vector<InfoElemCompra> resultat = txCC.obteResultat();

	for (unsigned int i = 0; i < resultat.size(); ++i) {
		std::cout << resultat[i].data << ": " << resultat[i].tipus << ' ' << resultat[i].nom << "; ";
		std::cout << resultat[i].descripcio << "; " << resultat[i].preu << " euros" << endl;

		if (resultat[i].tipus == "paquet") {
			std::cout << " Videojocs: " << endl;
			for (unsigned int j = 0; j < resultat[i].videojocs.size(); ++j) {
				std::cout << "      " << resultat[i].videojocs[j].nom << "; ";
				std::cout << resultat[i].videojocs[j].descripcio << endl;
			}
		}
	}

	std::cout << "Total: " << txCC.obteTotalEurosGastats() << " euros" << endl;
}

void CapaDePresentacio::consultarPaquet() {
	std::cout << "** Consultar paquet **" << endl;
	std::cout << "Nom paquet: ";
	std::string nomPaquet;
	getline(cin, nomPaquet);

	TxConsultarPaquets TxCP = TxConsultarPaquets();
	TxCP.posaNom(nomPaquet);
	TxCP.executar();
	if (TxCP.paquetExisteix) {
		vector<ResultatPaquet> resultat = TxCP.obteResultat();

		std::cout << "Informacio del paquet:" << endl;
		std::cout << "Nom paquet: " << resultat[0].nom << endl;
		std::cout << "Descripcio: " << resultat[0].descripcio << endl;
		std::cout << "Preu: " << resultat[0].preu;
		std::cout << " (estalvi de " << resultat[0].preuJocs - resultat[0].preu << " euros)" << endl << endl;

		std::cout << "Jocs inclosos:" << endl;
		for (unsigned int i = 0; i < resultat[0].videojocs.size(); ++i) {
			std::cout << "- " << resultat[0].videojocs[i].nom << "; ";
			std::cout << resultat[0].videojocs[i].descripcio << "; ";
			std::cout << resultat[0].videojocs[i].preu << " euros" << endl;
		}
	}
	else {
		std::cout << "No existeix cap paquet de videojocs amb aquest nom." << endl;
	}
}

void CapaDePresentacio::consultarPaquets() {
	std::cout << "** Consultar paquets **" << endl;
	TxConsultarPaquets TxCP = TxConsultarPaquets();
	TxCP.executar();

	vector<ResultatPaquet> resultat = TxCP.obteResultat();
	for (unsigned int i = 0; i < resultat.size(); ++i) {
		std::cout << resultat[i].nom << "; ";
		std::cout << resultat[i].descripcio << "; ";
		std::cout << resultat[i].preu;
		std::cout << " (estalvi de " << resultat[i].preuJocs - resultat[i].preu << " euros)" << endl;
	}
}

void CapaDePresentacio::consultarVideojoc() {
	std::cout << "** Consultar videojoc **" << endl;
	std::cout << "Nom videojoc: ";
	std::string consulta;
	getline(cin, consulta);
	TxConsultaVideojocs txCV = TxConsultaVideojocs();
	txCV.posaNomVideojoc(consulta);
	txCV.executar();

	if (txCV.videojocExistex) {
		std::cout << "Informacio del videojoc:" << endl;
		std::vector<ResultatInfoVideojoc> vd = txCV.obteResultat();
		std::cout << "Nom videojoc: " << vd[0].nom << endl;
		std::cout << "Descripcio: " << vd[0].descripcio << endl;
		std::cout << "Qualificacio per edat: " << vd[0].qEdat << endl;
		if (0 < vd[0].minsE) std::cout << "Temps estimat: " << vd[0].minsE << " minuts" << endl;
		std::cout << "Genere: " << vd[0].genere << endl;
		std::cout << "Data llansament: " << vd[0].dLlansament << endl;
		std::cout << "Preu: " << vd[0].preu << " euros" << endl;

		if (vd[0].paquetsOnSurt.size() != 0) std::cout << "Paquets on esta inclos: ";
		for (unsigned int i = 0; i < vd[0].paquetsOnSurt.size(); ++i) {
			std::cout << vd[0].paquetsOnSurt[i] << ' ';
		}
		std::cout << endl << endl;
	}
	else std::cout << "No existeix cap videojoc amb aquest nom." << endl;
}

void CapaDePresentacio::consultarVideojocs() {
	std::cout << "** Consultar videojocs **" << endl;

	TxConsultaVideojocs txCV = TxConsultaVideojocs();
	txCV.executar();
	std::vector<ResultatInfoVideojoc> vd = txCV.obteResultat();
	for (unsigned int i = 0; i < vd.size(); ++i) {
		std::cout << "Nom videojoc: " << vd[i].nom << endl;
		std::cout << "Descripcio: " << vd[i].descripcio << endl;
		std::cout << "Qualificacio per edat: " << vd[i].qEdat << endl;
		if (0 < vd[i].minsE) std::cout << "Temps estimat: " << vd[i].minsE << " minuts" << endl;
		std::cout << "Genere: " << vd[i].genere << endl;
		std::cout << "Data llansament: " << vd[i].dLlansament << endl;
		std::cout << "Preu: " << vd[i].preu << " euros" << endl;

		if (vd[i].paquetsOnSurt.size() != 0) std::cout << "Paquets on esta inclos: ";
		for (unsigned int j = 0; j < vd[i].paquetsOnSurt.size(); ++j) {
			std::cout << vd[i].paquetsOnSurt[j] << ' ';
		}
		std::cout << endl << "------------------------" << endl;
	}
}

void CapaDePresentacio::consultarVideojocsPerEdat() {
	std::cout << "** Consultar videojocs per edat **" << endl;
	int edat;
	std::cout << "Edat maxima (en anys): ";
	if (std::cin >> edat and edat > 0) {
		std::cin.ignore();
		TxConsultaVideojocs txCV = TxConsultaVideojocs();
		txCV.posaQualificacioEdat(edat);
		txCV.executar();

		std::vector<ResultatInfoVideojoc> vd = txCV.obteResultat();
		for (unsigned int i = 0; i < vd.size(); ++i) {
			std::cout << vd[i].nom << "; ";
			std::cout << vd[i].descripcio << "; ";
			std::cout << vd[i].preu << "; ";
			std::cout << vd[i].qEdat << " PEGI; ";
			std::cout << vd[i].genere << "; ";
			std::cout << vd[i].dLlansament << "; ";
			if (0 < vd[i].minsE) std::cout << "estimacio temps joc: " << vd[i].minsE << " minuts";
			
			if (vd[i].paquetsOnSurt.size() != 0) std::cout << "; Paquets: ";
			for (unsigned int j = 0; j < vd[i].paquetsOnSurt.size(); ++j) {
				std::cout << vd[i].paquetsOnSurt[j] << ' ';
			}
			std::cout << endl;
		}
	}
	else {
		cin.clear(); // Elimina totes les flags d'error
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
		std::cout << "Edat invalida. S'ha d'introduir un numero major que 0." << endl;
	}
}

void CapaDePresentacio::consultarNovetatsVideojocs() {
	std::cout << "** Consultar novetats **" << endl;
	std::cout << "Data (AAAA-MM-DD): ";
	std::string consulta;
	std::getline(cin, consulta);

	TxConsultaVideojocs txCV = TxConsultaVideojocs();
	txCV.cercaPerData = true;
	if (consulta.length() != 0) txCV.posaDataLlansament(consulta);
	txCV.executar();
	std::vector<ResultatInfoVideojoc> vd = txCV.obteResultat();
	for (unsigned int i = 0; i < vd.size(); ++i) {
		std::cout << vd[i].nom << "; ";
		std::cout << vd[i].descripcio << "; ";
		std::cout << vd[i].preu << "; ";
		std::cout << vd[i].qEdat << " PEGI; ";
		std::cout << vd[i].genere << "; ";
		std::cout << vd[i].dLlansament << "; ";
		if (0 < vd[i].minsE) std::cout << "estimacio temps joc: " << vd[i].minsE << " minuts";

		if (vd[i].paquetsOnSurt.size() != 0) std::cout << "; Paquets: ";
		for (unsigned int j = 0; j < vd[i].paquetsOnSurt.size(); ++j) {
			std::cout << vd[i].paquetsOnSurt[j] << ' ';
		}
		std::cout << endl;
	}
}
