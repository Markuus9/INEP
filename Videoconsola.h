#pragma once
#include <iostream>
using namespace std;

class Videoconsola
{
private:
    // Atributos
    struct Usuari {
        std::string nom;
        std::string sobrenom;
        std::string contrasenya;
        std::string correuElectronic;
        std::string dataNaixement;
    };
    struct Usuari usu;
    bool sessioiniciada;
    // Si sessioiniciada = false, les dades de usu no són vàlides.
    // Si sessioiniciada = true, usu conté les dades de l'Usuari que té
    // la sessió iniciada.

    // Constructor privat per prevenir la creació d'instàncies, la instància es crea a la operació getInstance()
    Videoconsola() {
        sessioiniciada = false;
    }

public:
    // Mètode per obtenir la única instància d'aquesta classe (ha de ser static i estar a .h)
    static Videoconsola& getInstance() {
        static Videoconsola instance;
        return instance;
    }

    // Mètodes per obtenir i modificar els atributs (getters/setters)
    struct Usuari obteUsuari();
    bool obteEstatSessio();
    std::string obteNomUsuari();
    std::string obteSobrenomUsuari();
    std::string obteContrasenyaUsuari();
    std::string obteCorreuElectronicUsuari();
    std::string obteDataNaixementUsuari();

    void canviaEstatSessio(bool estat);
    void modificarNomUsuari(std::string n);
    void modificarSobrenomUsuari(std::string sn);
    void modificarContrasenyaUsuari(std::string ct);
    void modificarCorreuElectronicUsuari(std::string ce);
    void modificarDataNaixementUsuari(std::string dn);

    // Altres
    //float complement(int antig);

};
