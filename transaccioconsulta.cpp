#include "transaccioconsulta.h"
#include "Videoconsola.h"

bool consultarVideojoc(std::string nomv, bool mostrarpaquets) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// Comprovem si "nomv" correspon al nom d'un Videojoc del sistema:
		std::string comanda = "SELECT nom, descripcio, preu FROM public.element_compra WHERE nom = ";
		comanda = comanda + "'" + nomv + "' and tipus = 'videojoc'";
		pqxx::result result = txn.exec(comanda);
		// result tindrà una fila o cap
		if (result.size() == 0 ) {
			std::cout << "No existeix cap videojoc amb aquest nom." << endl;
			return false;
		}
		else {
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
	return true;
}

bool consultarVideojocCompactat(std::string nomv, bool mostrarpaquets) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// Comprovem si "nomv" correspon al nom d'un Videojoc del sistema:
		std::string comanda = "SELECT nom, tipus from public.element_compra WHERE nom = ";
		comanda = comanda + "'" + nomv + "' and tipus = 'videojoc'";
		pqxx::result result = txn.exec(comanda);
		// result tindrà una fila o cap. Si té una fila, només tindrà una columna amb el nom de l'element compra
		if (result.size() == 0) {
			std::cout << "No existeix cap videojoc amb aquest nom." << endl;
			return false;
		}
		else {
			// Mostrem la informació del videojoc:
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
	return true;
}

void consultarVideojocs() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// Obtenim tots els videojocs del sistema ordenats descendentment per data de llançament:
		std::string comanda = "SELECT nom from videojoc ORDER BY data_llansament DESC";
		pqxx::result result = txn.exec(comanda);
		// Mostrem la informació de cada videojoc:
		for (size_t i = 0; i < result.size(); ++i) {
			std::string nomjoc = result[i][0].c_str();
			consultarVideojocCompactat(nomjoc, true);
			std::cout << endl;
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void consultarVideojocsPerEdat(int e) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		std::cout << "** Consultar videojocs fins a " << std::to_string(e) << " anys **" << endl;
		std::string comanda = "SELECT nom from videojoc WHERE qualificacio_edat <= ";
		comanda = comanda + std::to_string(e) + " ORDER BY qualificacio_edat DESC, data_llansament DESC";
		pqxx::result result = txn.exec(comanda);
		// Mostrem la informació de cada videojoc amb una qualificació d'edat menor o igual a "e"
		for (size_t i = 0; i < result.size(); ++i) {
			// result només té una columna
			std::string nomjoc = result[i][0].c_str();
			consultarVideojocCompactat(nomjoc, true);
			std::cout << endl;
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch(const std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void consultarNovetatsVideojocs(std::string data) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		std::string comanda = "SELECT nom from videojoc WHERE data_llansament >";
		pqxx::result result;
		if (data.size() == 0) {
			// Si "data" és un string buit, es posarà a "data" la data en la que s'executa la funció i
			// es buscaran els videojocs amb data de llançament MAJOR que avui.
			std::string comandadata = "SELECT current_date";
			result = txn.exec(comandadata);
			// result només té una fila i una columna, que indica la data en la que s'executa la comanda
			data = result[0][0].c_str();
		}
		else {
			// Si "data" no és un string buit, es buscaran els videojocs amb data de llançament major
			// O IGUAL a "data".
			comanda = comanda + '=';
		}
		comanda = comanda + " '" + data + "' ORDER BY data_llansament DESC";
		result = txn.exec(comanda);
		// Mostrem la informació de cada videojoc que es troba a "result":
		for (size_t i = 0; i < result.size(); ++i) {
			// result només té una columna
			std::string nomjoc = result[i][0].c_str();
			consultarVideojocCompactat(nomjoc, true);
			std::cout << endl;
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

bool consultarPaquet(std::string nomp) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// Comprovem si "nomp" correspon al nom d'un paquet de videojocs del sistema:
		std::string comanda = "SELECT nom, descripcio, preu FROM public.element_compra WHERE nom = ";
		comanda = comanda + "'" + nomp + "' and tipus = 'paquet'";
		pqxx::result result = txn.exec(comanda);
		// result tindrà una fila o cap
		if (result.size() == 0) {
			std::cout << "No existeix cap paquet de videojocs amb aquest nom." << endl;
			return false;
		}
		else {
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
	return true;
}

void consultarPaquets() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		std::string comanda = "SELECT nom, descripcio, preu FROM public.element_compra WHERE tipus = 'paquet'";
		pqxx:: result result = txn.exec(comanda);
		int preupaq = 0, preutotsjocspaquet = 0;
		for (size_t i = 0; i < result.size(); ++i) {
			for (size_t j = 0; j < result[i].size(); ++j) {
				if (j > 0) {
					std::cout << "; ";
				}
				std::cout << result[i][j].c_str();
				std::string camp = result[i][j].name();
				if (camp == "nom") {
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