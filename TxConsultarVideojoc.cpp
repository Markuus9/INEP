#include "TxConsultarVideojoc.h"

TxConsultarVideojoc::TxConsultarVideojoc(std::string nv, bool mostrarpaq) {
	nomv = nv;
	mostrarpaquets = mostrarpaq;
}

void TxConsultarVideojoc::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// Comprovem si "nomv" correspon al nom d'un Videojoc del sistema:
		// CERCADORA + PASAREL·LA??
		std::string comanda = "SELECT nom, descripcio, preu FROM public.element_compra WHERE nom = ";
		comanda = comanda + "'" + nomv + "' and tipus = 'videojoc'";
		pqxx::result result = txn.exec(comanda);
		// result tindrà una fila o cap
		if (result.size() == 0) {
			std::cout << "No existeix cap videojoc amb aquest nom." << endl;
			resultat = false;
		}
		else {
			resultat = true;
			// Mostrem la informació del videojoc:
			std::string preujoc;
			std::cout << "Informacio del videojoc:" << endl;
			for (size_t j = 0; j < result[0].size(); ++j) {
				std::string camp = result[0][j].name();
				if (camp == "nom") {
					std::cout << "Nom videojoc: " << result[0][j].c_str() << endl;
				}
				else if (camp == "descripcio") {
					std::cout << "Descripcio: " << result[0][j].c_str() << "." << endl;
				}
				else if (camp == "preu") {
					// El preu es mostrarà al final de la consulta
					preujoc = result[0][j].c_str();
				}
			}
			// CERCADORA + PASAREL·LA??
			comanda = "SELECT qualificacio_edat, data_llansament, mins_estimat, genere FROM public.Videojoc WHERE nom = ";
			comanda = comanda + "\'" + nomv + "\'";
			result = txn.exec(comanda);
			for (size_t j = 0; j < result[0].size(); ++j) {
				std::string camp = result[0][j].name();
				if (camp == "qualificacio_edat") {
					std::cout << "Qualificacio per edats: " << result[0][j].c_str() << endl;
				}
				else if (camp == "data_llansament") {
					std::cout << "Data llansament: " << result[0][j].c_str() << endl;
				}
				else if (camp == "mins_estimat") {
					string resposta = result[0][j].c_str();
					if (resposta.size() != 0) {
						std::cout << "Temps estimat: " << result[0][j].c_str() << " minuts." << endl;
					}
				}
				else if (camp == "genere") {
					std::cout << "Genere: " << result[0][j].c_str() << endl;
				}
			}
			std::cout << "Preu: " << preujoc << endl;
			if (mostrarpaquets) {
				comanda = "SELECT paquet FROM public.Conte WHERE videojoc = ";
				comanda = comanda + "\'" + nomv + "\'";
				result = txn.exec(comanda);
				if (result.size() > 0) {
					std::cout << "Paquets on esta inclos:";
					for (size_t i = 0; i < result.size(); ++i) {
						if (i > 0) {
							std::cout << ";";
						}
						std::cout << " " << result[i][0].c_str();
					}
					std::cout << endl;
				}
			}
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

bool TxConsultarVideojoc::obteResultat() {
	return resultat;
}