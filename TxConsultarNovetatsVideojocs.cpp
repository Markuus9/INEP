#include "TxConsultarNovetatsVideojocs.h"

TxConsultarNovetatsVideojocs::TxConsultarNovetatsVideojocs(std::string dataConsulta) {
	data = dataConsulta;
}

void TxConsultarNovetatsVideojocs::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// CERCADORA + PASAREL�LA??
		std::string comanda = "SELECT nom from videojoc WHERE data_llansament >";
		pqxx::result result;
		if (data.size() == 0) {
			// Si "data" �s un string buit, es posar� a "data" la data en la que s'executa la funci� i
			// es buscaran els videojocs amb data de llan�ament MAJOR que avui.
			std::string comandadata = "SELECT current_date";
			result = txn.exec(comandadata);
			// result nom�s t� una fila i una columna, que indica la data en la que s'executa la comanda
			data = result[0][0].c_str();
		}
		else {
			// Si "data" no �s un string buit, es buscaran els videojocs amb data de llan�ament major
			// O IGUAL a "data".
			comanda = comanda + '=';
		}
		comanda = comanda + " '" + data + "' ORDER BY data_llansament DESC";
		result = txn.exec(comanda);
		// Mostrem la informaci� de cada videojoc que es troba a "result":
		for (size_t i = 0; i < result.size(); ++i) {
			// result nom�s t� una columna
			std::string nomjoc = result[i][0].c_str();
			TxConsultarVideojocCompactat txconsulta(nomjoc, true);
			txconsulta.executa();
			// No recollim el valor que retorna el executa de la inst�ncia de
			// TxConsultarVideojocCompactat perqu� tenim garantit de que
			// nomjoc �s el nom d'un videojoc de la base de dades
			std::cout << endl;
		}
		// Confirmar la transacci�:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}