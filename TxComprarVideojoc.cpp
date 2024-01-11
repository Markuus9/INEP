#include "TxComprarVideojoc.h"

TxComprarVideojoc::TxComprarVideojoc(std::string nvideojoc) {
	n = nvideojoc;
}

void TxComprarVideojoc::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		try {
			// Busquem la qualificació per edats del videojoc, ja que ens servirà més endavant.
			// CERCADORA + PASAREL·LA??
			std::string comanda = "SELECT qualificacio_edat FROM public.Videojoc WHERE nom = ";
			comanda = comanda + "\'" + n + "\'";
			pqxx::result result = txn.exec(comanda);
			int edatjoc = atoi(result[0][0].c_str());

			// Comprovem si l'usuari ja ha comprat el videojoc amb anterioritat.
			Videoconsola& v = Videoconsola::getInstance();
			std::string sobrenomusu = v.obteSobrenomUsuari();
			// CERCADORA + PASAREL·LA??
			comanda = "SELECT * FROM public.Compra WHERE usuari = ";
			comanda = comanda + "\'" + sobrenomusu + "\' and element = " + "\'" + n + "\'";
			result = txn.exec(comanda);
			// Busquem per clau primària. "result" té una fila o no en té cap.
			if (result.size() == 1) {
				throw "Ja has comprat aquest joc anteriorment.";
			}
			
			// Comprovem si el videojoc és apropiat per l'edat de l'usuari.
			// CERCADORA + PASAREL·LA?? (si es muy difícil usar Age con pasarelas, no usar)
			comanda = "SELECT Age(data_naixement) from public.Usuari where sobrenom = ";
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
				// CERCADORA + PASAREL·LA??
				comanda = "SELECT preu FROM public.element_compra WHERE nom = ";
				comanda = comanda + "'" + n + "'";
				result = txn.exec(comanda);
				std::string preujoc = result[0][0].c_str();
				comanda = "SELECT current_timestamp";
				result = txn.exec(comanda);
				// Un exemple del que retorna la comanda: 2024-01-05 10:55:15.024597+01
				// En aquest cas, per enregistrar la data de la compra, només voldriem:
				//2024-01-05 10:55:15
				std::string resultat_timestamp = result[0][0].c_str();
				std::string datacompra;
				// Bucle per agafar la data i hora fins arribar al punt dels segons:
				for (unsigned int i = 0; resultat_timestamp[i] != '.'; ++i) {
					datacompra = datacompra + resultat_timestamp[i];
				}
				// Enregistrem la compra:
				// CREAR PASAREL·LA I FER INSEREIX??
				comanda = "INSERT INTO public.Compra VALUES (";
				comanda = comanda + "\'" + datacompra + "\', ";
				comanda = comanda + "\'" + sobrenomusu + "\', ";
				comanda = comanda + "\'" + n + "\', ";
				comanda = comanda + "\'" + preujoc + "\')";
				result = txn.exec(comanda);
				// Mostrar la data i hora de la compra:
				std::cout << "Compra registrada: " << datacompra << endl;
				// Buscar paquets on es troba el videojoc amb nom "n":
				// CERCADORA + PASAREL·LA??
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
					com2 = "SELECT v.nom, e.descripcio, e.preu FROM Videojoc v, Conte con, element_compra e WHERE con.videojoc = v.nom AND con.paquet = ";
					com2 = com2 + "\'" + nompaquet + "\'";
					com2 = com2 + " AND v.nom = e.nom AND v.data_llansament <= NOW() ORDER BY v.nom ASC";
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