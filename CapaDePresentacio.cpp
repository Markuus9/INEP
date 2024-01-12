#include "CapaDePresentacio.h"

void iniciSessio()
{
	std::cout << "** Inici sessio **" << std::endl;
	std::string sn, ct;
	std::cout << "Sobrenom: ";
	std::getline(cin, sn);
	std::cout << "Contrasenya: ";
	std::getline(cin, ct);
	TxIniciSessio& txIniciSessio(sn, ct);
}

void tancaSessio()
{
	
}

void registrarUsuari()
{
	std::cout << "** Registrar usuari **" << std::endl;
	std::cout << "Omplir la informacio que es demana..." << endl;
	std::string n, sn, ct, dn, ce;
	std::cout << "Nom complet: ";
	std::getline(cin, n);
	std::cout << "Sobrenom: ";
	std::getline(cin, sn);
	std::cout << "Contrasenya: ";
	std::getline(cin, ct);
	std::cout << "Correu electronic: ";
	std::getline(cin, ce);
	std::cout << "Data naixement (AAAA-MM-DD): ";
	std::getline(cin, dn);
	// registrarUsuari(n, sn, ct, ce, dn);
	
}

void consultaUsuari()
{
	std::cout << "** Consulta usuari **" << std::endl;
	// consultarUsuari(vc);
	std::cout << std::endl;
	// infoCompres(vc);
}

void modificaUsuari()
{

}

void esborraUsuari()
{

}