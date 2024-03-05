#include "PassarelaUsuari.h"
#include <pqxx/pqxx>
#include "arxiu_configuracio.h"

PassarelaUsuari::PassarelaUsuari() {
}

PassarelaUsuari::PassarelaUsuari(std::string sn, std::string n, std::string ct, std::string ce, std::string dn) {
	sobrenom = sn;
	nom = n;
	contrasenya = ct;
	correu_electronic = ce;
	data_naixement = dn;
}

std::string PassarelaUsuari::obteSobrenom() {
	return sobrenom;
}

std::string PassarelaUsuari::obteNom() {
	return nom;
}

std::string PassarelaUsuari::obteContrasenya() {
	return 	contrasenya;
}

std::string PassarelaUsuari::obteCorreuElectronic() {
	return correu_electronic;
}

std::string PassarelaUsuari::obteDataNaixement() {
	return data_naixement;
}

int PassarelaUsuari::obteEdat() const {
	// Comprovem si el videojoc �s apropiat per l'edat de l'usuari.
	pqxx::connection conn(connectionString);
	pqxx::work txn(conn);

	std::string comanda = "SELECT AGE(timestamp \'" + data_naixement + "\') from public.usuari WHERE sobrenom = ";
	comanda = comanda + "\'" + sobrenom + "\'";
	pqxx::result result = txn.exec(comanda);
	// Aquesta comanda retorna un resultat de tipus "X years Y mons Z days".
	// Nom�s ens interesa la X, que indiquen els anys de l'usuari.
	std::string resultatcomanda = result[0][0].c_str();
	std::string edat;
	for (unsigned int i = 0; resultatcomanda[i] != ' '; ++i) {
		edat = edat + resultatcomanda[i];
	}
	int edatusuari = std::atoi(edat.c_str());
	
	return edatusuari;
}

void PassarelaUsuari::insereix() const {
	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);
		// Comprovem si existeix algun usuari amb sobrenom "sobrenom":
		std::string comanda = "SELECT sobrenom FROM public.usuari WHERE sobrenom = \'" + sobrenom + "\'";
		pqxx::result result = txn.exec(comanda);
		bool error = false;
		if (result.size() != 0) {
			std::cout << "Ja existeix un usuari amb aquest sobrenom." << std::endl;
		}
		else {
			// Comprovem si existeix algun usuari amb correu electr�nic "correu_electronic":
			comanda = "SELECT correu_electronic FROM public.usuari WHERE correu_electronic = ";
			comanda = comanda + "\'" + correu_electronic + "\'";
			result = txn.exec(comanda);
			if (result.size() != 0) {
				std::cout << "Ja existeix un usuari amb aquest correu electronic." << std::endl;
			}
			else {
				// Inserim un nou usuari a la base de dades:
				comanda = "INSERT INTO public.usuari VALUES(";
				comanda = comanda + "\'" + nom + "\', ";
				comanda = comanda + "\'" + sobrenom + "\', ";
				comanda = comanda + "\'" + contrasenya + "\', ";
				comanda = comanda + "\'" + correu_electronic + "\', ";
				comanda = comanda + "\'" + data_naixement + "\')";
				result = txn.exec(comanda);
				std::cout << "Nou usuari registrat correctament!" << std::endl;
			}
		}
		txn.commit(); // Confirmar la transacci�
	}
	catch (const char* err) {
		std::cout << err << std::endl;
	}
}

void PassarelaUsuari::posaNom(std::string n) {
	nom = n;
}

void PassarelaUsuari::posaContrasenya(std::string c) {
	contrasenya = c;
}

void PassarelaUsuari::posaCorreuElectronic(std::string ce) {
	correu_electronic = ce;
}

void PassarelaUsuari::posaDataNaixement(std::string dn) {
	data_naixement = dn;
}

bool PassarelaUsuari::correuExisteix(std::string c) {
	bool correuExisteix = false;
	
	if (c.length() != 0) {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}

		pqxx::work txn(conn);
		std::string comanda = "SELECT correu_electronic FROM usuari ";
		comanda += "WHERE correu_electronic = '" + c + "';";
		pqxx::result result = txn.exec(comanda);
		if (result.size() != 0) correuExisteix = true;
	}
	
	return correuExisteix;
}

void PassarelaUsuari::modifica() const {
	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);
		std::string comanda = "UPDATE usuari SET ";
		comanda += " nom  = '" + nom + "',";
		comanda += " contrasenya  = '" + contrasenya + "',";
		comanda += " correu_electronic  = '" + correu_electronic + "',";
		comanda += " data_naixement  = '" + data_naixement + "'";
		comanda += " WHERE sobrenom = '" + sobrenom + "';";
		pqxx::result result = txn.exec(comanda);
		txn.commit(); // Confirmar la transaccio
	}
	catch (const char* err) {
		std::cout << err << std::endl;
	}
}

void PassarelaUsuari::esborra() const {
	try {
		pqxx::connection conn(connectionString);
		if (not conn.is_open()) {
			std::cerr << "Error de connexio amb la base de dades." << std::endl << std::endl;
		}
		pqxx::work txn(conn);

		std::string comanda = "DELETE FROM usuari WHERE sobrenom = '" + sobrenom + "';";
		pqxx::result result = txn.exec(comanda);
		
		txn.commit(); // Confirmar la transacci�
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}