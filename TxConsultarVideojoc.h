#pragma once
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
// #include "Transaccio.h"
#include "Videoconsola.h"
using namespace std;

class TxConsultarVideojoc //:  public Transaccio
{

public:
    // constructora
    TxConsultarVideojoc(std::string nv, bool mostrarpaq);

    // Si existeix a la base de dades algun videojoc amb nom "nomv", es mostra tota la informació
    // del videojoc. La informació que es mostra és el nom, descripció, preu, qualificació per edats,
    // gènere, data de llançament i temps estimat (si en té). Si el videojoc està algun paquet i
    // "mostrarpaquets" és true, es mostra el nom dels paquets en els quals el videojoc està.
    // Si "nomv" no correspon al nom de un videojoc de la base de dades, el valor de "resultat" serà
    // false. Altrament serà true.
    void executa(); // override;    

    // getter del resultat
    bool obteResultat();

private:
    std::string nomv;
    bool mostrarpaquets;
    bool resultat;
};

