#pragma once
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
// #include "Transaccio.h"
#include "Videoconsola.h"
using namespace std;

class TxConsultarPaquet //:  public Transaccio
{

public:
    // constructora
    TxConsultarPaquet(std::string np);

    // Si a la base de dades existeix algun paquet de videojocs de nom "nomp", es mostra el nom, descripció i preu del
    // paquet i l'estalvi en relacio a comprar tots els videojocs que conté per separat. També es mostra una llista dels
    // noms, descripcions i preus de tots els videojocs que conté el paquet ordenats ascendentment per nom. Si existeix
    // un paquet de videojocs a la base de dades amb nom "nomp", "resultat" valdrà true. Altrament valdrà false.
    void executa(); // override;    

    // getter del resultat
    bool obteResultat();

private:
    std::string nomp;
    bool resultat;
};

