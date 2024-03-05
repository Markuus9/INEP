#include "CercadoraConte.h"
#include "arxiu_configuracio.h"

std::vector<PassarelaConte> CercadoraConte::cercaPaquetsPerVideojoc(std::string nomV) {
	std::vector<PassarelaConte> resultat;

	try {
		pqxx::connection conn(connectionString);
		pqxx::work txn(conn);
		std::string comanda = "SELECT * FROM public.conte WHERE videojoc = '" + nomV + "';";
		pqxx::result result = txn.exec(comanda);

		// result: cada fila correspon a una parella de paquet i videojoc on el paquet inclou el videojoc
		for (size_t i = 0; i < result.size(); ++i) {
			// columna 0 de result: nom del paquet, columna 1 de result: nom del videojoc
			PassarelaConte conte = PassarelaConte(result[i][0].c_str(), result[i][1].c_str());
			resultat.push_back(conte);
		}
		
		txn.commit(); // Confirmar la transacci�
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return resultat;
}

std::vector<PassarelaConte> CercadoraConte::cercaVideojocsPerPaquet(std::string nomP) {
	std::vector<PassarelaConte> resultat;

	try {
		pqxx::connection conn(connectionString);
		pqxx::work txn(conn);
		std::string comanda = "SELECT * FROM public.conte WHERE paquet = '" + nomP + "';";
		pqxx::result result = txn.exec(comanda);

		// result: cada fila correspon a una parella de paquet i videojoc on el paquet inclou el videojoc
		for (size_t i = 0; i < result.size(); ++i) {
			// columna 0 de result: nom del paquet, columna 1 de result: nom del videojoc
			PassarelaConte conte = PassarelaConte(result[i][0].c_str(), result[i][1].c_str());
			resultat.push_back(conte);
		}

		txn.commit(); // Confirmar la transacci�
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return resultat;
}