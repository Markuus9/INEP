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

class TxConsultarVideojocsPerEdat //:  public Transaccio
{

public:
    // constructora
    TxConsultarVideojocsPerEdat(int edat);

    //// Pre: "e" és un enter major que 0
    // Mostra tota la informació dels videojocs apropiats per l’edat indicada per "e", és a dir, tots
    // els jocs on la qualificació d’edat sigui més petita o igual a "e" La llista de jocs estarà ordenada
    // descendentment per la qualificació d’edat i data de llançament. La informació del videojoc que es mostra
    // és el nom, descripció, preu, qualificació per edat, gènere, data de llançament i temps estimat (si en té).
    // Si el videojoc està en algun paquet, es mostra el nom dels paquets en els quals el videojoc està.
    void executa(); // override;

private:
    int e;
};

