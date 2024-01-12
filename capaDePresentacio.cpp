#include "capaDePresentacio.h"

void iniciSessio()
{
	std::cout << "** Inici sessio **" << std::endl;
	std::cout << "Sobrenom: ";
	string sn;
	std::getline(cin, sn);
	std::cout << "Contrasenya: ";
	string ct;
	std::getline(cin, ct);
	txIniciSessio& txIniciSessio(sn, ct);
}

void tancaSessio()
{
	transaccio& tx = transaccio::getInstance();
}

void registrarUsuari()
{
	transaccio& tx = transaccio::getInstance();
}

void consultaUsuari()
{
	transaccio& tx = transaccio::getInstance();
}

void modificaUsuari()
{
	transaccio& tx = transaccio::getInstance();
}

void esborraUsuari()
{
	transaccio& tx = transaccio::getInstance();
}