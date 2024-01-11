#include "TxConsultarCompres.h"

TxConsultarCompres::TxConsultarCompres() {
}

void TxConsultarCompres::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		Videoconsola& v = Videoconsola::getInstance();
		std::string sobrenomusu = v.obteSobrenomUsuari();
		string comanda = "SELECT data, element, preu_pagat FROM public.Compra WHERE Usuari = ";
		comanda = comanda + "\'" + sobrenomusu + "\' ORDER BY data DESC";
		pqxx::result result = txn.exec(comanda);
		int totalgastat = 0;
		bool espaquet = false;
		std::string nomelem;
		// Bucle per cada Compra:
		for (size_t i = 0; i < result.size(); ++i) {
			espaquet = false;
			for (size_t j = 0; j < result[i].size(); ++j) {
				std::string camp = result[i][j].name();
				if (camp == "data") {
					std::cout << result[i][j].c_str() << ":";
				}
				if (camp == "element") {
					nomelem = result[i][j].c_str();
					// Obtenim el nom, descripció i tipus de l'element:
					// CERCADORA + PASAREL·LA??
					std::string comandaelem = "SELECT tipus FROM public.element_compra WHERE nom = ";
					comandaelem = comandaelem + "\'" + nomelem + "\'";
					pqxx::result resultatelem = txn.exec(comandaelem);
					// result només té una fila i una columna
					std::string campelem = resultatelem[0][0].c_str();
					if (campelem == "videojoc") {
						std::cout << " videojoc";
					}
					else { // campelem == "paquet"
						std::cout << " paquet";
						espaquet = true;
					}
					// CERCADORA + PASAREL·LA??
					comandaelem = "SELECT nom, descripcio FROM public.element_compra WHERE nom = ";
					comandaelem = comandaelem + "\'" + nomelem + "\'";
					resultatelem = txn.exec(comandaelem);
					// Hem buscat per clau primària, així que resultatelem només té una fila.
					// Mostrar nom, descripció de l'element:
					for (size_t columna = 0; columna < resultatelem[0].size(); ++columna) {
						std::cout << " " << resultatelem[0][columna].c_str() << ";";
					}

				}
				if (camp == "preu_pagat") {
					totalgastat = totalgastat + atoi(result[i][j].c_str());
					std::cout << " " << result[i][j].c_str() << " euros" << endl;
				}
			}
			if (espaquet) {
				// Mostrem el contingut del paquet
				std::cout << "\t Videojocs:" << endl;
				std::string comandapaquet = "SELECT v.nom, e.descripcio FROM Videojoc v, Conte con, element_compra e WHERE con.videojoc = v.nom AND con.paquet = ";
				comandapaquet = comandapaquet + "\'" + nomelem + "\' AND v.nom = e.nom ORDER BY v.nom ASC";
				pqxx::result resultatinfo = txn.exec(comandapaquet);
				for (size_t i2 = 0; i2 < resultatinfo.size(); ++i2) {
					std::cout << "\t\t";
					for (size_t j2 = 0; j2 < resultatinfo[i2].size(); ++j2) {
						std::cout << " " << resultatinfo[i2][j2].c_str();
						std::cout << ";";
					}
					std::cout << endl;
				}
			}
			std::cout << endl;
		}
		std::cout << "Total: " << totalgastat << " euros" << endl;
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}