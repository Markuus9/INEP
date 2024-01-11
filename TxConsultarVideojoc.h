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

    // Si existeix a la base de dades algun videojoc amb nom "nomv", es mostra tota la informaci�
    // del videojoc. La informaci� que es mostra �s el nom, descripci�, preu, qualificaci� per edats,
    // g�nere, data de llan�ament i temps estimat (si en t�). Si el videojoc est� algun paquet i
    // "mostrarpaquets" �s true, es mostra el nom dels paquets en els quals el videojoc est�.
    // Si "nomv" no correspon al nom de un videojoc de la base de dades, el valor de "resultat" ser�
    // false. Altrament ser� true.
    void executa(); // override;    

    // getter del resultat
    bool obteResultat();

private:
    std::string nomv;
    bool mostrarpaquets;
    bool resultat;
};

