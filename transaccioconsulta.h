#pragma once
#ifndef _TXCONSULTA_H
#define _TXCONSULTA_H

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
using namespace std;

// Si existeix a la base de dades algun videojoc amb nom "nomv", es mostra tota la informació
// del videojoc. La informació que es mostra és el nom, descripció, preu, qualificació per edats,
// gènere, data de llançament i temps estimat (si en té). Si el videojoc està algun paquet i
// "mostrarpaquets" és true, es mostra el nom dels paquets en els quals el videojoc està.
// Si "nomv" no correspon al nom de un videojoc de la base de dades, es retornarà false.
// Altrament es retornarà true.
bool consultarVideojoc(std::string nomv, bool mostrarpaquets);


// Aquesta funció té el mateix funcionament que la funció "consultarVideojoc", pero la informació
// del videojoc es mostra sense fer salts de línia.
bool consultarVideojocCompactat(std::string nomv, bool mostrarpaquets);


// Mostra tota la informació de tots els videojocs de la base de dades. La informació que
// es mostra de cada videojoc és el nom, descripció, preu, qualificació per edats,
// gènere, data de llançament i temps estimat (si en té). Si el videojoc està algun paquet i
// "mostrarpaquets" és true, es mostra el nom dels paquets en els quals el videojoc està.
// Aquesta llista es mostra ordenada descendentment per data llançament.
void consultarVideojocs();

// Pre: "e" és un enter major que 0
// Mostra tota la informació dels videojocs apropiats per l’edat indicada per "e", és a dir, tots
// els jocs on la qualificació d’edat sigui més petita o igual a "e" La llista de jocs estarà ordenada
// descendentment per la qualificació d’edat i data de llançament. La informació del videojoc que es mostra
// és el nom, descripció, preu, qualificació per edat, gènere, data de llançament i temps estimat (si en té).
// Si el videojoc està en algun paquet, es mostra el nom dels paquets en els quals el videojoc està.
void consultarVideojocsPerEdat(int e);

// Mostra tota la informació dels videojocs que la seva data de llançament sigui més gran o igual a la data
// introduïda. Si "data" és un string buit, es mostrarà tota la informació dels videojocs amb data de llançament
// més gran que la data d'avui. La informació del videojoc que es mostra és el nom, descripció, preu, qualificació 
// per edat, data de llançament i temps estimat (si en té). Si el videojoc està en algun paquet, es mostra el nom
// dels paquets en els quals el videojoc està. La llista de videojoc estarà ordenada descendentment per data.
void consultarNovetatsVideojocs(std::string data);

// Si a la base de dades existeix algun paquet de videojocs de nom "nomp", es mostra el nom, descripció i preu del
// paquet i l'estalvi en relacio a comprar tots els videojocs que conté per separat. També es mostra una llista dels
// noms, descripcions i preus de tots els videojocs que conté el paquet ordenats ascendentment per nom. Retorna true
// si "nomp" correspon al nom d'un paquet de videojocs de la base de dades. Altrament retorna false.
bool consultarPaquet(std::string nomp);

// Mostra el nom, descripció, preu de tots els paquets de la base de dades. Per a cada paquet també es mostra
// l'estalvi (en euros) en relació amb comprar els videojocs que conté per separat.
void consultarPaquets();


#endif