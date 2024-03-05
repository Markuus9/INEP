#pragma once
#include <iostream>
#include "PassarelaUsuari.h"
#include <pqxx/pqxx>

class CercadoraUsuari
{	
public:
	CercadoraUsuari();
	PassarelaUsuari cercaUsuari(std::string sn);
};

