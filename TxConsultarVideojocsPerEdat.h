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

    //// Pre: "e" �s un enter major que 0
    // Mostra tota la informaci� dels videojocs apropiats per l�edat indicada per "e", �s a dir, tots
    // els jocs on la qualificaci� d�edat sigui m�s petita o igual a "e" La llista de jocs estar� ordenada
    // descendentment per la qualificaci� d�edat i data de llan�ament. La informaci� del videojoc que es mostra
    // �s el nom, descripci�, preu, qualificaci� per edat, g�nere, data de llan�ament i temps estimat (si en t�).
    // Si el videojoc est� en algun paquet, es mostra el nom dels paquets en els quals el videojoc est�.
    void executa(); // override;

private:
    int e;
};

