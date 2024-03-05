#include "CercadoraElemCompra.h"
#include "arxiu_configuracio.h"

std::vector<PassarelaElemCompra> CercadoraElemCompra::cercaElement(std::string nomElem) {
	std::vector<PassarelaElemCompra> resultat;

	pqxx::connection conn(connectionString);
	if (not conn.is_open()) {
		std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
	}
	pqxx::work txn(conn);

	std::string comanda = "SELECT * FROM public.element_compra ";
	comanda += "WHERE element_compra.nom = \'" + nomElem + "\';";
	pqxx::result result = txn.exec(comanda);

	// result �s una fila que correspon a un element_compra
	// si result �s buida significa que l'element_compra amb nom "nomElem" no existeix
	// columna 0: nom, columna 1: descripcio, columna 2: preu, columna3: tipus
	for (size_t i = 0; i < result.size(); ++i) {
		float p = atof(result[i][2].c_str());
		PassarelaElemCompra ec = PassarelaElemCompra(result[i][0].c_str(), result[i][1].c_str(), p, result[i][3].c_str());
		resultat.push_back(ec);

	}
	txn.commit();

	return resultat;
}

std::vector<PassarelaElemCompra> CercadoraElemCompra::cercaTotsElements() {
	std::vector<PassarelaElemCompra> resultat;

	pqxx::connection conn(connectionString);
	if (not conn.is_open()) {
		std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
	}
	pqxx::work txn(conn);

	std::string comanda = "SELECT * FROM public.element_compra;";
	pqxx::result result = txn.exec(comanda);

	// result: cada fila correspona a un element_compra
	// columna 0: nom, columna 1: descripcio, columna 2: preu, columna3: tipus
	for (size_t i = 0; i < result.size(); ++i) {
		float p = atof(result[i][2].c_str());
		PassarelaElemCompra ec = PassarelaElemCompra(result[i][0].c_str(), result[i][1].c_str(), p, result[i][3].c_str());
		resultat.push_back(ec);

	}
	txn.commit();

	return resultat;
}

std::vector<PassarelaElemCompra> CercadoraElemCompra::cercaTotsPaquets() {
	std::vector<PassarelaElemCompra> resultat;

	pqxx::connection conn(connectionString);
	if (not conn.is_open()) {
		std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
	}
	pqxx::work txn(conn);

	std::string comanda = "SELECT * FROM public.element_compra WHERE tipus = 'paquet';";
	pqxx::result result = txn.exec(comanda);

	// result: cada fila correspona a un element_compra
	// columna 0: nom, columna 1: descripcio, columna 2: preu, columna3: tipus
	for (size_t i = 0; i < result.size(); ++i) {
		float p = atof(result[i][2].c_str());
		PassarelaElemCompra ec = PassarelaElemCompra(result[i][0].c_str(), result[i][1].c_str(), p, result[i][3].c_str());
		resultat.push_back(ec);

	}
	txn.commit();

	return resultat;
}