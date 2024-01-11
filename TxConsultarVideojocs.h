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

    // Mostra tota la informaci� de tots els videojocs de la base de dades. La informaci� que
    // es mostra de cada videojoc �s el nom, descripci�, preu, qualificaci� per edats,
    // g�nere, data de llan�ament i temps estimat (si en t�). Tamb� es mostra el nom dels paquets
    // en els quals el videojoc est�.
    // Aquesta llista es mostra ordenada descendentment per data llan�ament.
    void executa(); // override;   
};

