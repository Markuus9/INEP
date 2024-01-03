#pragma once
#ifndef _TXCOMPRA_H
#define _TXCOMPRA_H

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
using namespace std;

// Si existeix un Videojoc amb nom "n" a la base de dades i l'usuari loggejat
// confirma la compra, s'enregistra a la base de dades la compra del Videojoc per part
// de l'usuari amb data corresponent a la data i hora en la que es fa la compra. Una vegada 
// enregistrada la compra, es mostra per pantalla la data i hora en la que s’ha registrat la compra
// i el nom, descripció i preu dels jocs que estan a paquets on es troba el videojoc comprat que estiguin
// disponibles per la compra ordenat ascendentment per nom (que la seva data de llançament sigui
// menor o igual a la data d’avui). Els videojocs que es mostren després de realitzar la compra es separen
// segons al paquet on estiguin. No es podrà realitzar la compra si el Videojoc no es adequat per
// a l'edat de l'usuari o si l'usuari ja l'ha comprat anteriorment.
void comprarVideojoc(std::string n);

// Si existeix un PaquetVideojocs amb nom "n" a la base de dades i l'usuari loggejat confirma la compra,
// s'enregistra a la base de dades la compra del PaquetVideojocs per part de l'usuari amb data corresponent a la
// data i hora en la que es fa la compra. Una vegada enregistrada la compra, es mostra la data corresponent a la
// data i hora en la que s'ha realitzat la compra.
void comprarPaquet(std::string n);

void consultarCompres();

#endif