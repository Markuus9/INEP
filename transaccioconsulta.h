#pragma once
#ifndef _TXCONSULTA_H
#define _TXCONSULTA_H

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
using namespace std;

// Si existeix a la base de dades algun videojoc amb nom "nomv", es mostra tota la informaci�
// del videojoc. La informaci� que es mostra �s el nom, descripci�, preu, qualificaci� per edats,
// g�nere, data de llan�ament i temps estimat (si en t�). Si el videojoc est� algun paquet i
// "mostrarpaquets" �s true, es mostra el nom dels paquets en els quals el videojoc est�.
// Si "nomv" no correspon al nom de un videojoc de la base de dades, es retornar� false.
// Altrament es retornar� true.
bool consultarVideojoc(std::string nomv, bool mostrarpaquets);


// Aquesta funci� t� el mateix funcionament que la funci� "consultarVideojoc", pero la informaci�
// del videojoc es mostra sense fer salts de l�nia.
bool consultarVideojocCompactat(std::string nomv, bool mostrarpaquets);


// Mostra tota la informaci� de tots els videojocs de la base de dades. La informaci� que
// es mostra de cada videojoc �s el nom, descripci�, preu, qualificaci� per edats,
// g�nere, data de llan�ament i temps estimat (si en t�). Si el videojoc est� algun paquet i
// "mostrarpaquets" �s true, es mostra el nom dels paquets en els quals el videojoc est�.
// Aquesta llista es mostra ordenada descendentment per data llan�ament.
void consultarVideojocs();

// Pre: "e" �s un enter major que 0
// Mostra tota la informaci� dels videojocs apropiats per l�edat indicada per "e", �s a dir, tots
// els jocs on la qualificaci� d�edat sigui m�s petita o igual a "e" La llista de jocs estar� ordenada
// descendentment per la qualificaci� d�edat i data de llan�ament. La informaci� del videojoc que es mostra
// �s el nom, descripci�, preu, qualificaci� per edat, g�nere, data de llan�ament i temps estimat (si en t�).
// Si el videojoc est� en algun paquet, es mostra el nom dels paquets en els quals el videojoc est�.
void consultarVideojocsPerEdat(int e);

// Mostra tota la informaci� dels videojocs que la seva data de llan�ament sigui m�s gran o igual a la data
// introdu�da. Si "data" �s un string buit, es mostrar� tota la informaci� dels videojocs amb data de llan�ament
// m�s gran que la data d'avui. La informaci� del videojoc que es mostra �s el nom, descripci�, preu, qualificaci� 
// per edat, data de llan�ament i temps estimat (si en t�). Si el videojoc est� en algun paquet, es mostra el nom
// dels paquets en els quals el videojoc est�. La llista de videojoc estar� ordenada descendentment per data.
void consultarNovetatsVideojocs(std::string data);

// Si a la base de dades existeix algun paquet de videojocs de nom "nomp", es mostra el nom, descripci� i preu del
// paquet i l'estalvi en relacio a comprar tots els videojocs que cont� per separat. Tamb� es mostra una llista dels
// noms, descripcions i preus de tots els videojocs que cont� el paquet ordenats ascendentment per nom. Retorna true
// si "nomp" correspon al nom d'un paquet de videojocs de la base de dades. Altrament retorna false.
bool consultarPaquet(std::string nomp);

// Mostra el nom, descripci�, preu de tots els paquets de la base de dades. Per a cada paquet tamb� es mostra
// l'estalvi (en euros) en relaci� amb comprar els videojocs que cont� per separat.
void consultarPaquets();


#endif