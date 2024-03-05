#include "PassarelaConte.h"

PassarelaConte::PassarelaConte(std::string nP, std::string nV) {
	nPaquet = nP;
	nVideojoc = nV;
}

std::string PassarelaConte::obteNomPaquet() {
	return nPaquet;
}

std::string PassarelaConte::obteNomVideojoc() {
	return nVideojoc;
}
