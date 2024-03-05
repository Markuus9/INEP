#include "CercadoraUsuari.h"
#include "PassarelaUsuari.h"
#include <pqxx/pqxx>
#include <iostream>
#include "arxiu_configuracio.h"

CercadoraUsuari::CercadoraUsuari() {

}

PassarelaUsuari CercadoraUsuari::cercaUsuari(std::string sn) {
	std::string n = " ", ct = " ", ce = " ", dn = " ";
	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);
		std::string comanda = "SELECT sobrenom, nom, contrasenya, correu_electronic, data_naixement ";
		comanda += "FROM public.usuari WHERE sobrenom = \'" + sn + "\'";
		pqxx::result result = txn.exec(comanda);
		
		if (result.size() == 0) {
			// no existeix usuari amb sobrenom sn a la base de dades
			std::cout <<  "Hi ha hagut un error amb el sobrenom o la contrasenya." << std::endl;
		}
		else {
			n = result[0][1].c_str();
			ct = result[0][2].c_str();
			ce = result[0][3].c_str();
			dn = result[0][4].c_str();
		}
		txn.commit(); // confirma la transacci�
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	PassarelaUsuari usu = PassarelaUsuari(sn, n, ct, ce, dn);
	return usu;
}