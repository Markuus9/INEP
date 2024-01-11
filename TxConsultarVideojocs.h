#pragma once
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
// #include "Transaccio.h"
#include "TxConsultarVideojocCompactat.h"
#include "Videoconsola.h"
using namespace std;

class TxConsultarVideojocs //:  public Transaccio
{

public:
    // constructora
    TxConsultarVideojocs();

    // Mostra tota la informació de tots els videojocs de la base de dades. La informació que
    // es mostra de cada videojoc és el nom, descripció, preu, qualificació per edats,
    // gènere, data de llançament i temps estimat (si en té). També es mostra el nom dels paquets
    // en els quals el videojoc està.
    // Aquesta llista es mostra ordenada descendentment per data llançament.
    void executa(); // override;   
};

