#include "CercadoraVideojocs.h"
#include <pqxx/pqxx>
#include "arxiu_configuracio.h"


std::vector<PassarelaVideojoc> CercadoraVideojocs::cercaVideojocPerNom(std::string nomV) {
	std::vector<PassarelaVideojoc> resultat;

	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		std::string comanda = "SELECT nom, qualificacio_edat, data_llansament, mins_estimat, genere FROM videojoc ";
		comanda += "WHERE videojoc.nom = \'" + nomV + "\';";
		pqxx::result result = txn.exec(comanda);

		// si result té una fila el videojoc amb nom "nomV" s'ha trobat, si result és buit el videojoc no existeix
		if (result.size() == 1) {
			int qE = atof(result[0][1].c_str());
			std::string mEstring = result[0][3].c_str();
			int mE = 0;
			if (mEstring.length() != 0) mE = atoi(result[0][3].c_str());
			// result 00: nom, result 01: qualificacio_edat, result 02: data_llansament
			// result 03: mins_estimat, result 04: genere 
			PassarelaVideojoc vd = PassarelaVideojoc(result[0][0].c_str(), qE, result[0][2].c_str(), mE, result[0][4].c_str());
			resultat.push_back(vd);
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return resultat;
}

std::vector<PassarelaVideojoc> CercadoraVideojocs::cercaTotsVideojocs() {
	std::vector<PassarelaVideojoc> resultat;

	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		std::string comanda = "SELECT * FROM videojoc ORDER BY data_llansament DESC;";
		pqxx::result result = txn.exec(comanda);

		// cada fila de result correspon a un videojoc
		for (size_t i = 0; i < result.size(); ++i) {
			int qE = atof(result[i][1].c_str());
			std::string mEstring = result[i][3].c_str();
			int mE = 0;
			if (mEstring.length() != 0) mE = atoi(result[i][3].c_str());
			// result 00: nom, result 01: qualificacio_edat, result 02: data_llansament
			// result 03: mins_estimat, result 04: genere 
			PassarelaVideojoc vd = PassarelaVideojoc(result[i][0].c_str(), qE, result[i][2].c_str(), mE, result[i][4].c_str());
			resultat.push_back(vd);
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return resultat;
}

std::vector<PassarelaVideojoc> CercadoraVideojocs::cercaVideojocsPerEdat(int edat) {
	std::vector<PassarelaVideojoc> resultat;

	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		std::string comanda = "SELECT * FROM videojoc WHERE qualificacio_edat <= " + std::to_string(edat);
		comanda += " ORDER BY qualificacio_edat DESC, data_llansament DESC";
		pqxx::result result = txn.exec(comanda);

		// cada fila de result correspon a un videojoc on qualificacio_edat <= edat
		for (size_t i = 0; i < result.size(); ++i) {
			int qE = atof(result[i][1].c_str());
			std::string mEstring = result[i][3].c_str();
			int mE = 0;
			if (mEstring.length() != 0) mE = atoi(result[i][3].c_str());
			// result 00: nom, result 01: qualificacio_edat, result 02: data_llansament
			// result 03: mins_estimat, result 04: genere 
			PassarelaVideojoc vd = PassarelaVideojoc(result[i][0].c_str(), qE, result[i][2].c_str(), mE, result[i][4].c_str());
			resultat.push_back(vd);
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return resultat;
}

std::vector<PassarelaVideojoc> CercadoraVideojocs::cercaVideojocsPerDataLlansament(std::string dataL) {
	std::vector<PassarelaVideojoc> resultat;

	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		std::string comanda = "SELECT * FROM videojoc WHERE data_llansament >";
		pqxx::result result;
		if (dataL == " ") {
			// Si "dataL" és un string buit, es posarà a "dataL" la data en la que s'executa la funció i
			// es buscaran els videojocs amb data de llansament MAJOR que avui.
			std::string comandaData = "SELECT current_date";
			result = txn.exec(comandaData);
			// result només té una fila i una columna, que indica la data en la que s'executa la comanda
			dataL = result[0][0].c_str();
		}
		else {
			// Si "dataL" no és un string buit, es buscaran els videojocs amb data de llansament major
			// O IGUAL a "datal".
			comanda += '=';
		}
		comanda += " '" + dataL + "' ORDER BY data_llansament DESC";
		result = txn.exec(comanda);

		// cada fila de result correspon a un videojoc on data_llansament >= dataL
		for (size_t i = 0; i < result.size(); ++i) {
			int qE = atof(result[i][1].c_str());
			std::string mEstring = result[i][3].c_str();
			int mE = 0;
			if (mEstring.length() != 0) mE = atoi(result[i][3].c_str());
			// result 00: nom, result 01: qualificacio_edat, result 02: data_llansament
			// result 03: mins_estimat, result 04: genere 
			PassarelaVideojoc vd = PassarelaVideojoc(result[i][0].c_str(), qE, result[i][2].c_str(), mE, result[i][4].c_str());
			resultat.push_back(vd);
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return resultat;
}
