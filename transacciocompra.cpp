#include "transacciocompra.h"
#include "Videoconsola.h"

void comprarVideojoc(std::string n) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		string comanda = "SELECT * FROM public.Videojoc WHERE nom = ";
		comanda = comanda + "\'" + n + "\'";
		pqxx::result result = txn.exec(comanda);
		try {
			// Comprovem si existeix un videojoc amb nom "n".
			if (result.size() != 1) {
				// Busquem per clau primària. "result" té una fila o no en té cap.
				throw "No existeix cap videojoc amb aquest nom.";
			}
			// Busquem la qualificació per edats del videojoc, ja que ens servirà més endavant.
			int edatjoc;
			for (size_t j = 0; j < result[0].size(); ++j) {
				std::string camp = result[0][j].name();
				if (camp == "qualificacioEdat") {
					edatjoc = atoi(result[0][j].c_str());
				}
			}

			// Comprovem si l'usuari ja ha comprat el videojoc amb anterioritat.
			Videoconsola& v = Videoconsola::getInstance();
			std::string sobrenomusu = v.obteSobrenomUsuari();
			comanda = "SELECT * FROM public.Compra WHERE usuari = ";
			comanda = comanda + "\'" + sobrenomusu + "\' and element = " + "\'" + n + "\'";
			result = txn.exec(comanda);
			// Busquem per clau primària. "result" té una fila o no en té cap.
			if (result.size() == 1) {
				throw "Ja has comprat aquest joc anteriorment.";
			}

			// Comprovem si el videojoc és apropiat per l'edat de l'usuari.
			comanda = "SELECT Age(\"dataNaixement\") from public.Usuari where sobrenom = ";
			comanda = comanda + "\'" + sobrenomusu + "\'";
			result = txn.exec(comanda);
			// Aquesta comanda retorna un resultat de tipus "X years Y mons Z days".
			// Només ens interesa la X, que indiquen els anys de l'usuari.
			std::string resultatcomanda = result[0][0].c_str();
			std::string edat;
			for (unsigned int i = 0; resultatcomanda[i] != ' '; ++i) {
				edat = edat + resultatcomanda[i];
			}
			int edatusuari = std::atoi(edat.c_str());
			if (edatusuari < edatjoc) {
				throw "El videojoc no es adequat per l'edat de l'usuari.";
			}

			// Mostrem la informació del videojoc:
			comanda = "SELECT nom, descripcio, preu FROM public.ElementCompra WHERE nom = ";
			comanda = comanda + "\'" + n + "\'";
			result = txn.exec(comanda);
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
					// El preu es mostrarà just abans de que l'usuari hagi de confirmar la compra
					preujoc = result[0][j].c_str();
				}
			}
			comanda = "SELECT \"qualificacioEdat\", \"dataLlansament\", \"minsEstimat\", genere FROM public.Videojoc WHERE nom = ";
			comanda = comanda + "\'" + n + "\'";
			result = txn.exec(comanda);
			for (size_t j = 0; j < result[0].size(); ++j) {
				std::string camp = result[0][j].name();
				if (camp == "qualificacioEdat") {
					std::cout << "Qualificacio per edats: " << result[0][j].c_str() << endl;
				}
				else if (camp == "dataLlansament") {
					std::cout << "Data llansament: " << result[0][j].c_str() << endl;
				}
				else if (camp == "minsEstimat") {
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
			std::cout << "Vols continuar amb la compra? (S/N): ";
			char resposta;
			bool sortir = false;
			while (not sortir) {
				std::cin >> resposta;
				if (resposta == 'S' or resposta == 'N') {
					sortir = true;
				}
			}
			std::cin.ignore(); // Per si en el futur es fa servir getline
			if (resposta == 'S') {
				comanda = "SELECT current_date";
				result = txn.exec(comanda);
				std::string datacompra = result[0][0].c_str();
				// Enregistrem la compra:
				comanda = "INSERT INTO public.Compra VALUES (";
				comanda = comanda + "\'" + datacompra + "\', ";
				comanda = comanda + "\'" + sobrenomusu + "\', ";
				comanda = comanda + "\'" + n + "\', ";
				comanda = comanda + "\'" + preujoc + "\')";
				result = txn.exec(comanda);
				// Mostrar la data i hora de la compra:
				std::cout << "Compra registrada: " << datacompra << endl;
				std::cout << "Jocs relacionats:" << endl;
				// Buscar paquets on es troba el videojoc amb nom "n":
				comanda = "SELECT paquet FROM public.Conte WHERE videojoc = ";
				comanda = comanda + "\'" + n + "\'";
				result = txn.exec(comanda);

				// Bucle per mostrar els jocs que es troben a cada paquet on es troba el videojoc de nom "n"
				// (i que ja hagin sigut llançats)
				for (size_t i = 0; i < result.size(); ++i) {
					// result només té una columna (que indica el nom de cada paquet
					// on es troba el videojoc amb nom "n")
					std::string nompaquet = result[i][0].c_str();
					std::cout << "Videojocs relacionats que es troben al paquet " << nompaquet << ":" << endl;
					std::string com2;
					com2 = "SELECT v.nom, e.descripcio, e.preu FROM Videojoc v, Conte con, ElementCompra e WHERE con.videojoc = v.nom AND con.paquet = ";
					com2 = com2 + "\'" + nompaquet + "\'";
					com2 = com2 + " AND v.nom = e.nom AND v.\"dataLlansament\" <= NOW() ORDER BY v.nom ASC";
					pqxx::result resultatinfo = txn.exec(com2);
					// Mostrem el nom, descripció i preu dels jocs que estan al paquet de nom "nompaquet",
					// exceptuant el videojoc amb nom "n":
					for (size_t i2 = 0; i2 < resultatinfo.size(); ++i2) {
						std::string nomjoc = resultatinfo[i2][0].c_str();
						if (nomjoc != n) {
							std::cout << "-";
							for (size_t j2 = 0; j2 < resultatinfo[i2].size(); ++j2) {
								std::cout << " " << resultatinfo[i2][j2].c_str();
								std::string campjoc = resultatinfo[i2][j2].name();
								if (campjoc == "preu") {
									std::cout << " euros";
								}
								std::cout << ";";
							}
							std::cout << endl;
						}
					}
					std::cout << endl;
				}
			}
			else {
				std::cout << "No s'ha efectuat la compra." << endl;
			}
		}
		catch (const char* err) {
			std::cout << err << endl;
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void comprarPaquet(std::string n) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		string comanda = "SELECT * FROM public.PaquetVideojocs WHERE nom = ";
		comanda = comanda + "\'" + n + "\'";
		pqxx::result result = txn.exec(comanda);
		try {
			// Comprovem si existeix un PaquetVideojocs amb nom "n".
			if (result.size() != 1) {
				// Busquem per clau primària. "result" té una fila o no en té cap.
				throw "No existeix cap paquet de videojocs amb aquest nom.";
			}

			// Comprovem si l'usuari ja ha comprat el PaquetVideojocs amb anterioritat.
			Videoconsola& v = Videoconsola::getInstance();
			std::string sobrenomusu = v.obteSobrenomUsuari();
			comanda = "SELECT * FROM public.Compra WHERE usuari = ";
			comanda = comanda + "\'" + sobrenomusu + "\' and element = " + "\'" + n + "\'";
			result = txn.exec(comanda);
			// Busquem per clau primària. "result" té una fila o no en té cap.
			if (result.size() == 1) {
				throw "Ja has comprat aquest paquet de videojocs anteriorment.";
			}

			// Mostrem la informació del PaquetVideojocs:
			comanda = "SELECT nom, descripcio, preu FROM public.ElementCompra WHERE nom = ";
			comanda = comanda + "\'" + n + "\'";
			result = txn.exec(comanda);
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
			comanda = "SELECT preujocs FROM public.preujocs where nompaquet = ";
			comanda = comanda + "\'" + n + "\'";
			result = txn.exec(comanda);
			// result només conté una fila i una columna, i conté la suma del preu de tots els
			// videojocs que conté el paquet de nom "n"
			int preutotsjocspaquet = atoi(result[0][0].c_str());
			std::cout << "Preu: " << preupaq << " (estalvi de " << preutotsjocspaquet - preupaq << " euros)" << endl;
			std::cout << endl;
			std::cout << "Jocs inclosos:" << endl;
			comanda = "SELECT v.nom, e.descripcio, e.preu FROM Videojoc v, Conte con, ElementCompra e WHERE con.videojoc = v.nom AND con.paquet = ";
			comanda = comanda + "\'" + n + "\' AND v.nom = e.nom ORDER BY v.nom ASC";
			pqxx::result resultatinfo = txn.exec(comanda);
			// Mostrem el nom, descripció i preu dels jocs que estan al paquet de nom "nompaquet":
			for (size_t i2 = 0; i2 < resultatinfo.size(); ++i2) {
				std::string nomjoc = resultatinfo[i2][0].c_str();
					std::cout << "-";
					for (size_t j2 = 0; j2 < resultatinfo[i2].size(); ++j2) {
						std::cout << " " << resultatinfo[i2][j2].c_str();
						std::string campjoc = resultatinfo[i2][j2].name();
						if (campjoc == "preu") {
							std::cout << " euros";
						}
						std::cout << ";";
					}
					std::cout << endl;
			}

			std::cout << "Vols continuar amb la compra? (S/N): ";
			char resposta;
			bool sortir = false;
			while (not sortir) {
				std::cin >> resposta;
				if (resposta == 'S' or resposta == 'N') {
					sortir = true;
				}
			}
			std::cin.ignore(); // Per si en el futur es fa servir getline
			if (resposta == 'S') {
				comanda = "SELECT current_date";
				result = txn.exec(comanda);
				std::string datacompra = result[0][0].c_str();
				// Enregistrem la compra:
				comanda = "INSERT INTO public.Compra VALUES (";
				comanda = comanda + "\'" + datacompra + "\', ";
				comanda = comanda + "\'" + sobrenomusu + "\', ";
				comanda = comanda + "\'" + n + "\', ";
				comanda = comanda + "\'" + std::to_string(preupaq) + "\')";
				result = txn.exec(comanda);
				// Mostrar la data i hora de la compra:
				std::cout << "Compra registrada: " << datacompra << endl;
			}
			else {
				std::cout << "No s'ha efectuat la compra." << endl;
			}
		}
		catch (const char* err) {
			std::cout << err << endl;
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void consultarCompres() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		Videoconsola& v = Videoconsola::getInstance();
		std::string sobrenomusu = v.obteSobrenomUsuari();
		string comanda = "SELECT data, element, \"preuPagat\" FROM public.Compra WHERE Usuari = ";
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
					std::string comandaelem = "SELECT nom, descripcio, tipus FROM public.ElementCompra WHERE nom = ";
					comandaelem = comandaelem + "\'" + nomelem + "\'";
					pqxx::result resultatelem = txn.exec(comandaelem);
					// Hem buscat per clau primària, així que resultatelem només té una fila.
					// Mostrar nom, descripció de l'element:
					for (size_t columna = 0; columna < resultatelem[0].size(); ++columna) {
						std::string campelem = resultatelem[0][columna].name();
						if (campelem == "tipus") {
							std::string tipus = resultatelem[0][columna].c_str();
							// Comprovem si l'element es un paquet:
							if (tipus == "paquet") {
								espaquet = true;
							}
						}
						else {
							std::cout << " " << resultatelem[0][columna].c_str() << ";";
						}
					}

				}
				if (camp == "preuPagat") {
					totalgastat = totalgastat + atoi(result[i][j].c_str());
					std::cout << " " << result[i][j].c_str() << " euros" << endl;
				}
			}
			if (espaquet) {
				// Mostrem el contingut del paquet
				std::cout << "\t Videojocs:" << endl;
				std::string comandapaquet = "SELECT v.nom, e.descripcio FROM Videojoc v, Conte con, ElementCompra e WHERE con.videojoc = v.nom AND con.paquet = ";
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