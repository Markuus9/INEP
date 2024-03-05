#pragma once
#include <iostream>

class PassarelaUsuari
{
private:
	// atributs
	std::string sobrenom;
	std::string nom;
	std::string contrasenya;
	std::string correu_electronic;
	std::string data_naixement;

public:
	// constructores
	PassarelaUsuari();
	PassarelaUsuari(std::string sn, std::string n, std::string ct, std::string ce, std::string dn);

	// getters
	std::string obteSobrenom();
	std::string obteNom();
	std::string obteContrasenya();
	std::string obteCorreuElectronic();
	std::string obteDataNaixement();

	int obteEdat() const;

	void insereix() const;

	// setters
	void posaNom(std::string n);
	void posaContrasenya(std::string c);
	void posaCorreuElectronic(std::string ce);
	void posaDataNaixement(std::string dn);

	bool correuExisteix(std::string c);
	void modifica() const;

	void esborra() const;
};

