#include "TxComprarPaquet.h"

TxComprarPaquet::TxComprarPaquet(std::string npaquet) {
	n = npaquet;
}

void TxComprarPaquet::executa(std::string n) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		try {
			// Comprovem si l'usuari ja ha comprat el paquet de videojocs amb anterioritat.
			Videoconsola& v = Videoconsola::getInstance();
			std::string sobrenomusu = v.obteSobrenomUsuari();
			// CERCADORA + PASAREL·LA??
			std::string comanda = "SELECT * FROM public.Compra WHERE usuari = ";
			comanda = comanda + "\'" + sobrenomusu + "\' and element = " + "\'" + n + "\'";
			pqxx::result result = txn.exec(comanda);
			// Busquem per clau primària. "result" té una fila o no en té cap.
			if (result.size() == 1) {
				throw "Ja has comprat aquest paquet de videojocs anteriorment.";
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
				std::string preupaq = result[0][0].c_str();
				comanda = "SELECT current_timestamp";
				result = txn.exec(comanda);
				// Un exemple del que retorna la comanda: 2024-01-05 10:55:15.024597+01
				// En aquest cas, per enregistrar la data de la compra, només necessitariem:
				// 2024-01-05 10:55:15
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
				comanda = comanda + "\'" + preupaq + "\')";
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