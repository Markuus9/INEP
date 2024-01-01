#include "transacciousuari.h"
#include "Videoconsola.h"

void iniciSessio(std::string sn, std::string ct) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		if (conn.is_open()) {
			std::cout << "Connexió exitosa amb la base de dades." << std::endl <<
				std::endl;
		}
		else {
			std::cerr << "Error de connexió amb la base de dades." << std::endl <<
				std::endl;
		}
		pqxx::work txn(conn);
		string comanda = "SELECT contrasenya FROM public.\"Usuari\" WHERE sobrenom = ";
		comanda = comanda + "\'" + sn + "\'";
		pqxx::result result = txn.exec(comanda);
		try {
			if (result.size() != 1 or (result.size() == 1 and result[0][0].c_str() != ct)) {
				// Busquem per clau primària. "result" té una fila o no en té cap.
				// Mirem la primera columna (i única) del resultat, que és la contrasenya:
				throw "Hi ha hagut un error amb el sobrenom o la contrasenya.";
			}
			else {
				Videoconsola& v = Videoconsola::getInstance();
				v.canviaEstatSessio(true);
				// Busquem la resta dels atributs de l'usuari per guardar la informació a la instància
				// de Videoconsola:
				string comanda = "SELECT * FROM public.\"Usuari\" WHERE sobrenom = ";
				comanda = comanda + "\'" + sn + "\'";
				pqxx::result result = txn.exec(comanda);
				for (size_t i = 0; i < result.size(); ++i) {
					for (size_t j = 0; j < result[i].size(); ++j) {
						std::string camp = result[i][j].name();
						if (camp == "nom") {
							v.modificarNomUsuari(result[i][j].c_str());
						}
						else if (camp == "sobrenom") {
							v.modificarSobrenomUsuari(result[i][j].c_str());
						}
						else if (camp == "contrasenya") {
							v.modificarContrasenyaUsuari(result[i][j].c_str());
						}
						else if (camp == "correuElectronic") {
							v.modificarCorreuElectronicUsuari(result[i][j].c_str());
						}
						else if (camp == "dataNaixement") {
							v.modificarDataNaixementUsuari(result[i][j].c_str());
						}
					}
				}
			}
		}
		catch (const char* err) {
			std::cout << err << endl;
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void registrarUsuari(std::string n, std::string sn, std::string ct, std::string ce, std::string dn) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		if (conn.is_open()) {
			std::cout << "Connexió exitosa amb la base de dades." << std::endl <<
				std::endl;
		}
		else {
			std::cerr << "Error de connexió amb la base de dades." << std::endl <<
				std::endl;
		}
		pqxx::work txn(conn);
		// Comprovem si existeix algun usuari amb sobrenom "sn":
		string comanda = "SELECT sobrenom FROM public.\"Usuari\" WHERE sobrenom = ";
		comanda = comanda + "\'" + sn + "\'";
		pqxx::result result = txn.exec(comanda);
		bool error = false;
		if (result.size() != 0) {
			std::cout << "Ja existeix un usuari amb aquest sobrenom." << endl;
		}
		else {
			// Comprovem si existeix algun usuari amb correu electrònic "ce":
			comanda = "SELECT \"correuElectronic\" FROM public.\"Usuari\" WHERE \"correuElectronic\" = ";
			comanda = comanda + "\'" + ce + "\'";
			result = txn.exec(comanda);
			if (result.size() != 0) {
				std::cout << "Ja existeix un usuari amb aquest correu electronic." << endl;
			}
			else {
				// Inserim un nou usuari a la base de dades:
				comanda = "INSERT INTO public.\"Usuari\" VALUES(";
				comanda = comanda + "\'" + n + "\', ";
				comanda = comanda + "\'" + sn + "\', ";
				comanda = comanda + "\'" + ct + "\', ";
				comanda = comanda + "\'" + ce + "\', ";
				comanda = comanda + "\'" + dn + "\')";
				result = txn.exec(comanda);
				std::cout << "Nou usuari registrat correctament!" << endl;
			}
		}
		// Confirmar la transacció:
		txn.commit();
	}
	catch (const char* err) {
		std::cout << err << endl;
	}
}