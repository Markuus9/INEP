#include "TxConsultarPaquets.h"

TxConsultarPaquets::TxConsultarPaquets() {
}

void TxConsultarPaquets::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// CERCADORA + PASAREL·LA??
		std::string comanda = "SELECT nom, descripcio, preu FROM public.element_compra WHERE tipus = 'paquet'";
		pqxx::result result = txn.exec(comanda);
		int preupaq = 0, preutotsjocspaquet = 0;
		for (size_t i = 0; i < result.size(); ++i) {
			for (size_t j = 0; j < result[i].size(); ++j) {
				if (j > 0) {
					std::cout << "; ";
				}
				std::cout << result[i][j].c_str();
				std::string camp = result[i][j].name();
				if (camp == "nom") {
					// Vista que representa l'atribut derivat preuJocs de PaquetVideojocs, que el volem calculat:
					std::string comanda = "SELECT preu_jocs FROM public.preu_jocs where nompaquet = ";
					comanda = comanda + "\'" + result[i][j].c_str() + "\'";
					pqxx::result resultatpreu = txn.exec(comanda);
					// resultatpreu només conté una fila i una columna, i conté la suma del preu de tots els
					// videojocs que conté el paquet de nom "n"
					preutotsjocspaquet = atoi(resultatpreu[0][0].c_str());
				}
				if (camp == "preu") {
					std::cout << " euros";
					preupaq = atoi(result[i][j].c_str());
				}
			}
			std::cout << " (estalvi de " << preutotsjocspaquet - preupaq << " euros)" << endl;
		}
		std::cout << endl;
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}