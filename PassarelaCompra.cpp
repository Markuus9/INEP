#include "PassarelaCompra.h"
#include <pqxx/pqxx>
#include "arxiu_configuracio.h"


PassarelaCompra::PassarelaCompra(std::string d, std::string u, std::string e, float p) {
	data = d;
	usuari = u;
	element = e;
	preu_pagat = p;
}

std::string PassarelaCompra::obteData() {
	return data;
}

std::string PassarelaCompra::obteUsuari() {
	return usuari;
}

std::string PassarelaCompra::obteElement() {
	return element;
}

float PassarelaCompra::obtePreuPagat() const {
	return preu_pagat;
}

void PassarelaCompra::posaDataCompra(std::string dc) {
	data = dc;
}

std::string PassarelaCompra::dataCompra() {
	std::string dataCompra;

	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		std::string comanda = "SELECT current_timestamp";
		pqxx::result result = txn.exec(comanda);

		// Un exemple del que retorna la comanda: 2024-01-05 10:55:15.024597+01
		// En aquest cas, per enregistrar la data de la compra, només necessitariem:
		// 2024-01-05 10:55:15
		std::string resultat_timestamp = result[0][0].c_str();
		// Bucle per agafar la data i hora fins arribar al punt dels segons:
		for (unsigned int i = 0; resultat_timestamp[i] != '.'; ++i) {
			dataCompra += resultat_timestamp[i];
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return dataCompra;
}

void PassarelaCompra::insereix() {
	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		// Enregistrem la compra:
		std::string comanda = "INSERT INTO public.compra VALUES (";
		comanda = comanda + "\'" + data + "\', ";
		comanda = comanda + "\'" + usuari + "\', ";
		comanda = comanda + "\'" + element + "\', ";
		comanda = comanda + "\'" + std::to_string(preu_pagat) + "\')";
		pqxx::result result = txn.exec(comanda);
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}



