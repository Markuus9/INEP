#include "PassarelaPreuJocs.h"

PassarelaPreuJocs::PassarelaPreuJocs(std::string np, float pj) {
	nom_paquet = np;
	preu_jocs = pj;
}

std::string PassarelaPreuJocs::obteNomPaquet() {
	return nom_paquet;
}

float PassarelaPreuJocs::obtePreuJocs() {
	return preu_jocs;
}
