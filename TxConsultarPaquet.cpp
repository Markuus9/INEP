#include "TxConsultarPaquet.h"

TxConsultarPaquet::TxConsultarPaquet(std::string np) {
	nomp = np;
}

void TxConsultarPaquet::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// Comprovem si "nomp" correspon al nom d'un paquet de videojocs del sistema:
		// CERCADORA + PASAREL·LA??
		std::string comanda = "SELECT nom, descripcio, preu FROM public.element_compra WHERE nom = ";
		comanda = comanda + "'" + nomp + "' and tipus = 'paquet'";
		pqxx::result result = txn.exec(comanda);
		// result tindrà una fila o cap
		if (result.size() == 0) {
			std::cout << "No existeix cap paquet de videojocs amb aquest nom." << endl;
			resultat = false;
		}
		else {
			resultat = true;
			int preupaq;
			std::cout << "Informacio del paquet:" << endl;
			for (size_t j = 0; j < result[0].size(); ++j) {
				std::string camp = result[0][j].name();
				if (camp == "nom") {
					std::cout << "Nom paquet: " << result[0][j].c_str() << endl;
				}
				else if (camp == "descripcio") {
					std::cout << "Descripcio: " << result[0][j].c_str() << "." << endl;
				}
				else if (camp == "preu") {
					// El preu es mostrarà just abans de mostrar els videojocs que conté el paquet
					preupaq = atoi(result[0][j].c_str());
				}
			}

			// Vista que representa l'atribut derivat preuJocs de PaquetVideojocs, que el volem calculat:
			comanda = "SELECT preu_jocs FROM public.preu_jocs where nompaquet = ";
			comanda = comanda + "\'" + nomp + "\'";
			result = txn.exec(comanda);
			// result només conté una fila i una columna, i conté la suma del preu de tots els
			// videojocs que conté el paquet de nom "n"
			int preutotsjocspaquet = atoi(result[0][0].c_str());
			std::cout << "Preu: " << preupaq << " (estalvi de " << preutotsjocspaquet - preupaq << " euros)" << endl;
			std::cout << endl;
			std::cout << "Jocs inclosos:" << endl;
			comanda = "SELECT e.nom, e.descripcio, e.preu FROM Conte con, element_compra e WHERE con.videojoc = e.nom AND con.paquet = ";
			comanda = comanda + "\'" + nomp + "\' ORDER BY e.nom ASC";
			pqxx::result resultatinfo = txn.exec(comanda);
			// Mostrem el nom, descripció i preu dels jocs que estan al paquet de nom "nompaquet":
			for (size_t i2 = 0; i2 < resultatinfo.size(); ++i2) {
				std::string nomjoc = resultatinfo[i2][0].c_str();
				std::cout << "-";
				for (size_t j2 = 0; j2 < resultatinfo[i2].size(); ++j2) {
					if (j2 > 0) {
						std::cout << ";";
					}
					std::cout << " " << resultatinfo[i2][j2].c_str();
					std::string campjoc = resultatinfo[i2][j2].name();
					if (campjoc == "preu") {
						std::cout << " euros";
					}
				}
				std::cout << endl;
			}
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

bool TxConsultarPaquet::obteResultat() {
	return resultat;
}