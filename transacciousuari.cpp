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
		string comanda = "SELECT contrasenya FROM public.usuari WHERE sobrenom = ";
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
				string comanda = "SELECT * FROM public.usuari WHERE sobrenom = ";
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
						else if (camp == "correu_electronic") {
							v.modificarCorreuElectronicUsuari(result[i][j].c_str());
						}
						else if (camp == "data_naixement") {
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
		string comanda = "SELECT sobrenom FROM public.usuari WHERE sobrenom = ";
		comanda = comanda + "\'" + sn + "\'";
		pqxx::result result = txn.exec(comanda);
		bool error = false;
		if (result.size() != 0) {
			std::cout << "Ja existeix un usuari amb aquest sobrenom." << endl;
		}
		else {
			// Comprovem si existeix algun usuari amb correu electrònic "ce":
			comanda = "SELECT correu_electronic FROM public.usuari WHERE correu_electronic = ";
			comanda = comanda + "\'" + ce + "\'";
			result = txn.exec(comanda);
			if (result.size() != 0) {
				std::cout << "Ja existeix un usuari amb aquest correu electronic." << endl;
			}
			else {
				// Inserim un nou usuari a la base de dades:
				comanda = "INSERT INTO public.usuari VALUES(";
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

void consultarUsuari(Videoconsola& vc) {
	std::cout << "Nom complet: " << vc.obteNomUsuari() << std::endl;
	std::cout << "Sobrenom: " << vc.obteSobrenomUsuari() << std::endl;
	std::cout << "Correu electronic: " << vc.obteCorreuElectronicUsuari() << std::endl;
	std::cout << "Data naixement (AAAA-MM-DD): " << vc.obteDataNaixementUsuari() << std::endl;
}

void infoCompres(Videoconsola& vc) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		if (not conn.is_open()) {
			std::cerr << "Error de connexió amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		// result: taula on cada fila correspon a un element comprat per l'usuari amb sobrenom vc.usu.sobrenom
		// columna 0: nom de l'element comprat, columna 1: preu pagat de l'element comprat
		string comanda = "SELECT compra.element, compra.preu_pagat FROM compra ";
		comanda += "WHERE compra.usuari = \'" + vc.obteSobrenomUsuari() + "\';";
		pqxx::result result = txn.exec(comanda);
		
		int videojocsComprats = 0;
		int paquetsComprats = 0;
		float eurosGastats = 0;

		for (size_t i = 0; i < result.size(); ++i) { 
			eurosGastats += atof(result[i][0].c_str()); // es va sumant el preu dels elements pagats per vc.usu

			string element = result[i][0].c_str();
			comanda = "SELECT tipus FROM element_compra WHERE element_compra.nom = \'" + element + "\';";
			pqxx::result result_aux = txn.exec(comanda); // result aux es una matriu 1x1 que conte el tipus de element
			
			string tipus = result_aux[0][0].c_str();
			if (tipus == "videojoc") ++videojocsComprats;
			else ++paquetsComprats;
		}
		txn.commit(); // confirma transacció

		std::cout << videojocsComprats << " videojoc";
		if (videojocsComprats != 1) std::cout << "s"; 
		std::cout << " comprat";
		if (videojocsComprats != 1) std::cout << "s"; 

		std::cout << endl << paquetsComprats << " paquet";
		if (paquetsComprats != 1) std::cout << "s";
		std::cout << " de videojocs comprat";
		if (paquetsComprats != 1) std::cout << "s";

		std::cout << endl << eurosGastats << " euros gastats en total" << endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void esborraUsuari(Videoconsola& vc, std::string ct, std::string& ctCorrecte) {
	if (ct != vc.obteContrasenyaUsuari()) {
		ctCorrecte = false;
		std::cout << "La contrasenya no és correcta" << std::endl;
	}
	else {
		try {
			pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
			if (not conn.is_open()) {
				std::cerr << "Error de connexió amb la base de dades." << std::endl << std::endl;
			}
			pqxx::work txn(conn);

			string comanda = "DELETE FROM usuari WHERE sobrenom = '" + vc.obteSobrenomUsuari() + "';";
			pqxx::result result = txn.exec(comanda);
			try {
				std::cout << "Usuari esborrat correctament!" << std::endl;
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
}

void modificarUsuari(Videoconsola& vc) {
	std::cout << "Omplir la informacio que es vol modificar..." << std::endl;
	std::string novaInfo;
	bool error = false;
	std::cout << "Nom complet: ";
	cin.ignore();
	std::getline(std::cin, novaInfo);
	if (novaInfo.length() != 0) {
		vc.modificarNomUsuari(novaInfo);
		modificarUsuariAux(vc.obteSobrenomUsuari(), "nom", novaInfo, error);
	}
	std::cout << "Contrasenya: ";
	std::getline(std::cin, novaInfo);
	if (novaInfo.length() != 0) {
		vc.modificarContrasenyaUsuari(novaInfo);
		modificarUsuariAux(vc.obteContrasenyaUsuari(), "contrasenya", novaInfo, error);
		std::cout << std::endl;
	}
	std::cout << "Correu electronic: ";
	std::getline(std::cin, novaInfo);
	if (novaInfo.length() != 0) {
		vc.modificarCorreuElectronicUsuari(novaInfo);
		modificarUsuariAux(vc.obteCorreuElectronicUsuari(), "correu_electronic", novaInfo, error);
		if (not error) vc.modificarCorreuElectronicUsuari(novaInfo);
		else return;
	}
	std::cout << "Data de naixement (DD/MM/AAAA): ";
	std::getline(std::cin, novaInfo);
	if (novaInfo.length() != 0) {
		std::cin >> novaInfo;
		vc.modificarDataNaixementUsuari(novaInfo);
		modificarUsuariAux(vc.obteSobrenomUsuari(), "data_naixement", novaInfo, error);
	}
	std::cout << "** Dades usuari modificades **" << std::endl;
}

void modificarUsuariAux(std::string sn, std::string camp, std::string novaInfo, bool& error) {
	try {
		pqxx::connection conn("dbname=SistemaGestioVideojocs user=postgres password=inep2023 hostaddr = 127.0.0.1 port = 5432");
		if (not conn.is_open()) {
			std::cerr << "Error de connexió amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);
		string comanda;
		if (camp == "correu_electronic") {
			comanda = "SELECT correu_electronic FROM public.usuari WHERE correu_electronic = '";
			comanda += novaInfo + "';";
			pqxx::result result = txn.exec(comanda);
			if (result.size() != 0) error = true;
		}
		if (error) std::cout << "El correu electronic ja existeix";
		else {
			comanda = "UPDATE usuari SET " + camp + " = '" + novaInfo + "' WHERE sobrenom = '" + sn + "';";
			pqxx::result result = txn.exec(comanda);
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

std::string confirmarContrasenya() {
	std::string contrasenya;

	char caracter = _getch();
	while (caracter != 13)
	{
		contrasenya += caracter;
		cout << '*';
		caracter = _getch();
	}
	std::cout << endl;
	return contrasenya;
}


