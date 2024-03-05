// gestioVideojocs.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include "Videoconsola.h"
#include "CapaDePresentacio.h"
#include "arxiu_configuracio.h"

std::string connectionString = "dbname=postgres user=postgres password=180402abcsql hostaddr = 127.0.0.1 port = 5432";


int main()
{
	Videoconsola& vc = Videoconsola::getInstance();
	
	bool sortir = false;
	int opcio;

	while ((not vc.obteEstatSessio()) and (not sortir)) {
		CapaDePresentacio& presentacio = CapaDePresentacio::getInstance();

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
			case 1: presentacio.iniciSessio();
				break;
			case 2: presentacio.registrarUsuari();
				break;
			case 3: sortir = true;
				break;
			}
		}
		else {
			cin.clear(); // Elimina totes les flags d'error
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
		}

		while (vc.obteEstatSessio() and (not sortir)) {
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
				case 4: presentacio.tancaSessio();
					break;
				case 5: sortir = true;
					break;
				}

				if (vc.obteEstatSessio() and (not sortir)) {
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
							std::string ct;
							bool ctCorrecte = true;
							switch (opcio) {
								case 1: presentacio.consultaUsuari();
									break;
								case 2: presentacio.modificaUsuari();
									break;
								case 3: presentacio.esborraUsuari(gestioUsuari);
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
								case 1: presentacio.comprarVideojoc();
									break;
								case 2: presentacio.comprarPaquet();
									break;
								case 3: presentacio.consultarCompres();
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
								case 1: presentacio.consultarVideojoc();
									break;
								case 2: presentacio.consultarVideojocs();
									break;
								case 3: presentacio.consultarVideojocsPerEdat();
									break;
								case 4: presentacio.consultarNovetatsVideojocs();
									break;
								case 5: presentacio.consultarPaquet();
									break;
								case 6: presentacio.consultarPaquets();
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
			else {
				cin.clear(); // Elimina totes les flags d'error
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora l'input
			}
		}
	}
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
