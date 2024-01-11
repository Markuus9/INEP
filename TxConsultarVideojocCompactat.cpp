#include "TxConsultarVideojocCompactat.h"

TxConsultarVideojocCompactat::TxConsultarVideojocCompactat(std::string nv, bool mostrarpaq) {
	nomv = nv;
	mostrarpaquets = mostrarpaq;
}

void TxConsultarVideojocCompactat::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// Comprovem si "nomv" correspon al nom d'un Videojoc del sistema:
		// CERCADORA + PASAREL·LA??
		std::string comanda = "SELECT nom, tipus from public.element_compra WHERE nom = ";
		comanda = comanda + "'" + nomv + "' and tipus = 'videojoc'";
		pqxx::result result = txn.exec(comanda);
		// result tindrà una fila o cap. Si té una fila, només tindrà una columna amb el nom de l'element compra
		if (result.size() == 0) {
			std::cout << "No existeix cap videojoc amb aquest nom." << endl;
			resultat = false;
		}
		else {
			resultat = true;
			// Mostrem la informació del videojoc:
			// CERCADORA + PASAREL·LA??
			comanda = "SELECT nom, descripcio, preu FROM public.element_compra WHERE nom = ";
			comanda = comanda + "\'" + nomv + "\'";
			result = txn.exec(comanda);
			std::string preujoc;
			for (size_t j = 0; j < result[0].size(); ++j) {
				std::string camp = result[0][j].name();
				if (j > 0) {
					std::cout << "; ";
				}
				std::cout << result[0][j].c_str();
				if (camp == "preu") {
					std::cout << " euros";
				}
			}
			// CERCADORA + PASAREL·LA??
			comanda = "SELECT qualificacio_edat, data_llansament, mins_estimat, genere FROM public.Videojoc WHERE nom = ";
			comanda = comanda + "\'" + nomv + "\'";
			result = txn.exec(comanda);
			for (size_t j = 0; j < result[0].size(); ++j) {
				std::string camp = result[0][j].name();
				if (camp != "mins_estimat" or (camp == "mins_estimat" and result[0][j].size() != 0)) {
					std::cout << "; " << result[0][j].c_str();
					if (camp == "mins_estimat") {
						std::cout << " minuts";
					}
					else if (camp == "qualificacio_edat") {
						std::cout << " PEGI";
					}
				}
			}
			if (mostrarpaquets) {
				// CERCADORA + PASAREL·LA??
				comanda = "SELECT paquet FROM public.Conte WHERE videojoc = ";
				comanda = comanda + "\'" + nomv + "\'";
				result = txn.exec(comanda);
				// result només té una columna amb el nom de cada paquet on es trobi el videojoc
				// amb nom "nomv"
				if (result.size() > 0) {
					std::cout << "; Paquets:";
					for (size_t i = 0; i < result.size(); ++i) {
						if (i > 0) {
							std::cout << ";";
						}
						std::cout << " " << result[i][0].c_str();
					}
				}
			}
			std::cout << endl;
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

bool TxConsultarVideojocCompactat::obteResultat() {
	return resultat;
}