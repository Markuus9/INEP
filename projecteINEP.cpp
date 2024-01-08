// projecteINEP.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <list>
#include <set>
#include <iomanip>
#include <fstream>
#include "Videoconsola.h"
#include "transacciousuari.h"
#include "transacciocompra.h"
#include "transaccioconsulta.h"
#include "projecteINEP.h"
using namespace std;
int main() {
	try {
		// Per establir la connexió amb la base de dades, es crea una pqxx::connection
		// per confirmar el port heu de mirar en el pgAdmin, a les properties hi ha una pestanya "Connection"
		// l'usuari postgres és el superusuari que s'ha creat durant la instal·lació del postgreSQL
		// heu de posar la contrasenya que heu escollit durant el procés d'instal·lació
		// Fem una primera connexió amb la base de dades per garantir que totes les funcions que el programa
		// farà servir podran connectar-se a la base de dades. Si la connexió dóna error, no es podrà executar
		// el programa.
		std::ifstream arxiu("C:\\Users\\mario\\Desktop\\UPC\\INEP\\arxiu_configuracio.txt");
		std::string arxcon;
		std::getline(arxiu, arxcon);
		pqxx::connection conn(arxcon);
		if (conn.is_open()) {
			std::cout << "Connexió exitosa amb la base de dades." << std::endl <<
			std::endl;
		}
		else {
			std::cerr << "Error de connexió amb la base de dades." << std::endl <<
			std::endl;
			return 1;
		}

		// Per realitzar una consulta...
		// 1.- es crea un pqxx::work amb la connexió que hem creat
		pqxx::work txn(conn);
		Videoconsola& vc = Videoconsola::getInstance();
		int opcio;
		bool fi = false;
		while (vc.obteEstatSessio() == false and fi != true) {
			std::cout << "******************" << std::endl;
			std::cout << "  Menu Principal  " << std::endl;
			std::cout << "******************" << std::endl;
			std::cout << "1. Iniciar sessio" << std::endl;
			std::cout << "2. Registrar usuari" << std::endl;
			std::cout << "3. Sortir" << std::endl;
			std::cout << "Opcio: ";
			std::string n, sn, ct, ce, dn;
			if (std::cin >> opcio) {
				std::cin.ignore();
				switch (opcio) {
				case 1: std::cout << "** Inici sessio **" << std::endl;
					std::cout << "Sobrenom: ";
					std::getline(cin, sn);
					std::cout << "Contrasenya: ";
					std::getline(cin, ct);
					iniciSessio(sn, ct);
					break;
				case 2: std::cout << "** Registrar usuari **" << std::endl;
					std::cout << "Omplir la informacio que es demana..." << endl;
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
					registrarUsuari(n, sn, ct, ce, dn);
					break;
				case 3: fi = true;
					break;
				}
			}
			else {
				cin.clear(); // Elimina totes les flags d'error
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
			}

			// Usuari loggejat
			while (vc.obteEstatSessio() and (not fi)) {
				std::cout << "******************" << std::endl;
				std::cout << "  Menu Principal  " << std::endl;
				std::cout << "******************" << std::endl;
				std::cout << "1. Gestionar usuari" << std::endl;
				bool gestioUsuari = false;
				std::cout << "2. Gestionar compres" << std::endl;
				bool gestioCompres = false;
				std::cout << "3. Consultar" << std::endl;
				bool consultesVideojocs = false;
				std::cout << "4. Tancar sessio" << std::endl;
				std::cout << "5. Sortir" << std::endl;
				std::cout << "Opcio: ";
				if (std::cin >> opcio) {
					switch (opcio) {
					case 1: gestioUsuari = true;
						break;
					case 2: gestioCompres = true;
						break;
					case 3: consultesVideojocs = true;
						break;
					case 4: vc.canviaEstatSessio(false);
						break;
					case 5: fi = true;
						break;
					}
				}
				else {
					cin.clear(); // Elimina totes les flags d'error
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
				}
				if (vc.obteEstatSessio() and (not fi)) {
					while (gestioUsuari) {
						std::cout << "--------------------" << std::endl;
						std::cout << "  Gestionar usuari  " << std::endl;
						std::cout << "--------------------" << std::endl;
						std::cout << "1. Consultar usuari" << std::endl;
						std::cout << "2. Modificar usuari" << std::endl;
						std::cout << "3. Esborrar usuari" << std::endl;
						std::cout << "4. Tornar" << std::endl;
						std::cout << "Opcio: ";
						if (std::cin >> opcio) {
							std::cin.ignore();
							switch (opcio) {
							case 1: std::cout << "** Consulta usuari **" << std::endl;
								consultarUsuari(vc);
								std::cout << std::endl;
								infoCompres(vc);
								break;
							case 2: std::cout << "** Modifica usuari **" << std::endl;
								consultarUsuari(vc);
								std::cin.peek() == '\n';
								modificarUsuari(vc);
								std::cin.peek() == '\n';
								consultarUsuari(vc);
								break;
							case 3: std::cout << "** Esborrar usuari **" << std::endl;
								std::cout << "Per confirmar l'esborrat, s'ha d'entrar la contrasenya..." << std::endl;
								std::cout << "Contrasenya: ";
								std::string ct;
								std::cin >> ct;
								esborraUsuari(vc, ct);
								break;
							case 4: gestioUsuari = false;
								break;
							}
						}
						else {
							cin.clear(); // Elimina totes les flags d'error
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
						}
					}

					while (gestioCompres) {
						std::cout << "--------------------" << std::endl;
						std::cout << "  Gestionar compres  " << std::endl;
						std::cout << "--------------------" << std::endl;
						std::cout << "1. Comprar videojoc" << std::endl;
						std::cout << "2. Comprar paquet videojoc" << std::endl;
						std::cout << "3. Consultar compres" << std::endl;
						std::cout << "4. Tornar" << std::endl;
						std::cout << "Opcio: ";
						if (std::cin >> opcio) {
							std::cin.ignore();
							std::string nom;
							switch (opcio) {
							case 1: std::cout << "** Comprar videojoc **" << endl;
								std::cout << "Nom videojoc: ";
								std::getline(cin, nom);
								comprarVideojoc(nom);
								break;
							case 2: std::cout << "** Comprar paquet **" << endl;
								std::cout << "Nom paquet: ";
								std::getline(cin, nom);
								comprarPaquet(nom);
								break;
							case 3: std::cout << "** Consultar compres **" << endl;
								consultarCompres();
								break;
							case 4: gestioCompres = false;
								break;
							}
						}
						else {
							cin.clear(); // Elimina totes les flags d'error
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
						}

					}

					while (consultesVideojocs) {
						std::cout << "--------------------" << std::endl;
						std::cout << "  Consultes videojocs  " << std::endl;
						std::cout << "--------------------" << std::endl;
						std::cout << "1. Consultar videojoc" << std::endl;
						std::cout << "2. Consultar videojocs" << std::endl;
						std::cout << "3. Consultar videojoc per edat" << std::endl;
						std::cout << "4. Consultar novetats videojocs" << std::endl;
						std::cout << "5. Consultar paquet videojocs" << std::endl;
						std::cout << "6. Consultar paquets videojocs" << std::endl;
						std::cout << "7. Tornar" << std::endl;
						std::cout << "Opcio: ";
						if (std::cin >> opcio) {
							std::cin.ignore();
							std::string consulta;
							switch (opcio) {
							case 1: std::cout << "** Consultar videojoc **" << endl;
								std::cout << "Nom videojoc: ";
								std::getline(cin, consulta);
								consultarVideojoc(consulta, true);
								break;
							case 2: std::cout << "** Consultar videojocs **" << endl;
								consultarVideojocs();
								break;
							case 3: std::cout << "** Consultar videojocs per edat **" << endl;
								int edat;
								std::cout << "Edat maxima (en anys): ";
								if (std::cin >> edat and edat > 0) {
									cin.ignore();
									consultarVideojocsPerEdat(edat);
								}
								else {
									cin.clear(); // Elimina totes les flags d'error
									cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
									std::cout << "Edat invalida. S'ha d'introduir un numero major que 0." << endl;
								}
								break;
							case 4: std::cout << "** Consultar novetats **" << endl;
								std::cout << "Data (AAAA-MM-DD): ";
								std::getline(cin, consulta);
								consultarNovetatsVideojocs(consulta);
								break;
							case 5: std::cout << "** Consultar paquet **" << endl;
								std::cout << "Nom paquet: ";
								std::getline(cin, consulta);
								consultarPaquet(consulta);
								break;
							case 6: std::cout << "** Consultar paquets **" << endl;
								consultarPaquets();
								break;
							case 7: consultesVideojocs = false;
								break;
							}
						}
						else {
							cin.clear(); // Elimina totes les flags d'error
							cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
						}
					}
				}
			}

			/* Comandos de prueba
			// 2.- s'executa una comanda en SQL que correspon a la consulta
			pqxx::result result = txn.exec("SELECT * FROM public.\"Usuari\"");
			// si a l'executar us dóna el missatge que no troba la taula, potser necessiteu posar :
			// "SELECT * FROM public.musics" o ""SELECT * FROM public.\"MUSICS\"
				// podeu confirmar la sintaxi de la comanda en el pgAdmin, sobre la taula escollir la opció Scripts\SELECT Script
				// Per mostrar el resultat de la consulta, hem de recórrer les files
				// (primer for) ...
				std::cout << "--------------------------------------------" << std::endl;
				std::cout << "Opció de recorrer el resultat amb dos loops" << std::endl;
			std::cout << "-------------------------------------------" << std::endl;
			for (const auto& row : result) {
				// ... i per cada fila, es recorren els camps (l'ordre és el que es veu a les columnes al pgAdmin
					for (const auto& field : row) {
						std::cout << field.name() << ": " << field.c_str() << "\t";
					}
				std::cout << std::endl;
			}
			// també es poden recórrer els resultats com si fosin una matriu de files i columnes(amb indexos començant per 0)
			std::cout << "---------------------------------------------" << std::endl;
			std::cout << "Opció de recorrer el resultat com una matriu" << std::endl;
			std::cout << "---------------------------------------------" << std::endl;
			for (size_t i = 0; i < result.size(); ++i) {
				for (size_t j = 0; j < result[i].size(); ++j) {
					std::cout << result[i][j].name() << ": " << result[i][j].c_str() <<
						"\t";
				}
				std::cout << std::endl;
			}
			std::cout << "---------------------------------------------" << std::endl;
			std::cout << "PROVA2: Opció de recorrer el NOU resultat com una matriu" << std::endl;
			std::cout << "---------------------------------------------" << std::endl;
			result = txn.exec("SELECT sobrenom FROM public.\"Usuari\"");
			for (size_t i = 0; i < result.size(); ++i) {
				for (size_t j = 0; j < result[i].size(); ++j) {
					std::cout << result[i][j].name() << ": " << result[i][j].c_str() <<
						"\t";
				}
				std::cout << std::endl;
			}
			*/
			// Finalment, s'ha de confirmar la transacción
			txn.commit();
			// La connexió es tanca automàticament al sortir del try
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
