#pragma once
#ifndef _TXUSUARI_H
#define _TXUSUARI_H

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
using namespace std;

// Si existeix a la base de dades un Usuari amb sobrenom "sn" i contrasenya "ct", es
// guarda a v.usu, on v és la instància singleton de Videoconsola, el nom, sobrenom,
// contrasenya, correu electrònic i data de naixement de l'usuari amb sobrenom sn.
// Altrament es produeix un error
void iniciSessio(std::string sn, std::string ct);

// Si no existeix a la base de dades cap Usuari amb sobrenom "sn" i/o correu electrònic "ct", 
// s'insereix un nou Usuari a la base de dades amb nom "n", sobrenom "sn", contrasenya "ct",
// correu electrònic "ce" i data "dn". Altrament es produeix un error
void registrarUsuari(std::string n, std::string sn, std::string ct, std::string ce, std::string dn);

// vc.usu és l'usuari loggejat
// mostra el nom, sobrenom, correu electrònic i data de naixement de vc.usu
void consultarUsuari(Videoconsola& vc);

// vc.usu és l'usuari loggejat
// mostra el nombre de videojocs i paquets comprats i la quantitat d'euros gastats per vc.usu
void infoCompres(Videoconsola& vc);

// vc.usu és l'usuari loggejat
// vc.usu té un o més dels atributs següents modificats: nom, contrasenya, correuElectronic o dataNaixement
void modificarUsuari(Videoconsola& vc);

// sn és el sobrenom de l'usuari del qual es volen canviar alguns atributs
// camp és la columna/atribut que es vol modificar i novaInfo serà el nou valor d'aquest camp
// error serà true si es vol canviar el correuElectronic per un ja existent
// a la BBDD l'usuari amb sobrenom sn queda modificat si no hi ha errors
void modificarUsuariAux(std::string sn, std::string camp, std::string novaInfo, bool& error);

// vc.usu és l'usuari loggejat i ct és la contrasenya demanada per esborrar
// si la ct no és vc.usu.contrasenya llavors ctCorrecte serà false
// Altrament ctCorrecte és true i s'esborrarà l'usuari
void esborraUsuari(Videoconsola& vc, std::string ct, bool& ctCorrecte);

// es retorna la contrasenya posada per l'usuari per confirmar-la
// quan la contrasenya és entrada no es mostra per pantalla per raons de seguretat
std::string confirmarContrasenya();

#endif
