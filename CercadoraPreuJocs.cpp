#include "CercadoraPreuJocs.h"
#include <pqxx/pqxx>
#include "arxiu_configuracio.h"

PassarelaPreuJocs CercadoraPreuJocs::cercaPreuJocs(std::string nomP) {
	pqxx::connection conn(connectionString);
	pqxx::work txn(conn);
	std::string comanda = "SELECT * FROM public.preu_jocs WHERE nom_paquet = '" + nomP + "';";
	pqxx::result result = txn.exec(comanda);

	// la fila result correspon a un paquet i preu_jocs (la suma dels preus de
	// tots els jocs que conte)
	// columna 0: nom del paquet, columna 1: preu dels jocs
	float preuJocs = atof(result[0][1].c_str());
	PassarelaPreuJocs resultat = PassarelaPreuJocs(result[0][0].c_str(), preuJocs);
		
	txn.commit(); // Confirmar la transacció

	return resultat;
}
