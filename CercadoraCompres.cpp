#include "CercadoraCompres.h"
#include <pqxx/pqxx>
#include <iostream>
#include "arxiu_configuracio.h"

std::vector<PassarelaCompra> CercadoraCompres::cercaCompraPerUsuari(std::string sobrenomU) {
	std::vector<PassarelaCompra> compres;
	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		std::string comanda = "SELECT * FROM compra ";
		comanda += "WHERE compra.usuari = \'" + sobrenomU + "\';";
		pqxx::result result = txn.exec(comanda);
		
		// cada fila de result correspon a una compra feta per l'usuari amb sobrenom "sobrenomU"
		for (size_t i = 0; i < result.size(); ++i) { 
			float p = atof(result[i][3].c_str());
			// result i0: data, result i1: usuari, result i2: element, result i3: preu_pagat de la compra i
			PassarelaCompra compra = PassarelaCompra(result[i][0].c_str(), result[i][1].c_str(), result[i][2].c_str(), p);
			compres.push_back(compra);
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return compres;
}

std::vector<PassarelaCompra> CercadoraCompres::cercaCompra(std::string sobrenomU, std::string nomEl) {
	std::vector<PassarelaCompra> compres;

	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		std::string comanda = "SELECT * FROM compra ";
		comanda += "WHERE compra.usuari = \'" + sobrenomU + "\' AND ";
		comanda += "compra.element = '" + nomEl + "';";
		pqxx::result result = txn.exec(comanda);

		// sí result té una fila l'usuari amb sobrenom "sobrenomU" ha comprat el videojoc amb nom "nomV"
		// altrament result és buit, osigui que tal compra no s'ha efectuat
		for (size_t i = 0; i < result.size(); ++i) {
			float p = atof(result[i][3].c_str());
			// result i0: data, result i1: usuari, result i2: element, result i3: preu_pagat de la compra i
			PassarelaCompra compra = PassarelaCompra(result[i][0].c_str(), result[i][1].c_str(), result[i][2].c_str(), p);
			compres.push_back(compra);
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return compres;
}
