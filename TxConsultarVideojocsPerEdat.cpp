#include "TxConsultarVideojocsPerEdat.h"

TxConsultarVideojocsPerEdat::TxConsultarVideojocsPerEdat(int edat) {
	e = edat;
}

void TxConsultarVideojocsPerEdat::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		std::cout << "** Consultar videojocs fins a " << std::to_string(e) << " anys **" << endl;
		// CERCADORA + PASAREL·LA??
		std::string comanda = "SELECT nom from videojoc WHERE qualificacio_edat <= ";
		comanda = comanda + std::to_string(e) + " ORDER BY qualificacio_edat DESC, data_llansament DESC";
		pqxx::result result = txn.exec(comanda);
		// Mostrem la informació de cada videojoc amb una qualificació d'edat menor o igual a "e"
		for (size_t i = 0; i < result.size(); ++i) {
			// result només té una columna
			std::string nomjoc = result[i][0].c_str();
			TxConsultarVideojocCompactat txconsulta(nomjoc, true);
			txconsulta.executa();
			// No recollim el valor que retorna el executa de la instància de
			// TxConsultarVideojocCompactat perquè tenim garantit de que
			// nomjoc és el nom d'un videojoc de la base de dades
			std::cout << endl;
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}