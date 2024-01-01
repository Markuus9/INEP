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


#endif