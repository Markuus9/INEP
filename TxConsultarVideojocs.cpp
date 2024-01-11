#include "TxConsultarVideojocs.h"

TxConsultarVideojocs::TxConsultarVideojocs() {
}

void TxConsultarVideojocs::executa() {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		// Obtenim tots els videojocs del sistema ordenats descendentment per data de llançament:
		// CERCADORA + PASAREL·LA??
		std::string comanda = "SELECT nom from videojoc ORDER BY data_llansament DESC";
		pqxx::result result = txn.exec(comanda);
		// Mostrem la informació de cada videojoc:
		for (size_t i = 0; i < result.size(); ++i) {
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