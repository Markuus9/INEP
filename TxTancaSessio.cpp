#include "TxTancaSessio.h"
#include "Videoconsola.h"
#include <iostream>

TxTancaSessio::TxTancaSessio() {

}

void TxTancaSessio::executar() {
	Videoconsola& vc = Videoconsola::getInstance();
	vc.tancaSessio();
	vc.canviaEstatSessio(false);
}