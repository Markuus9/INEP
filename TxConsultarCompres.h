#pragma once
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <pqxx/pqxx>
// #include "Transaccio.h"
#include "Videoconsola.h"
using namespace std;

class TxConsultarCompres //:  public Transaccio
{

public:
    // constructora
    TxConsultarCompres();

    //Post: Es mostra la llista amb la data de compra, nom, descripció i preu de l'element per totes les compres realitzades
    // per l’usuari i el total gastat. Quan la compra és d’un paquet, també es mostrarà la llista de noms dels videojocs
    // continguts al paquet. Aquesta llista estarà ordenada descendentment per data de compra.
    void executa(); // override;    

};