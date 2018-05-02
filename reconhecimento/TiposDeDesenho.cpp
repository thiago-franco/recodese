#include "TiposDeDesenho.h"

TiposDeDesenho::TiposDeDesenho()
{
}

int TiposDeDesenho::quantidadeDeTipos()
{
	return NUVEM + 1; // TODO: atualizar caso seja adicionado novo tipo
}

string TiposDeDesenho::emString(int tipo)
{
	string tipoEmTexto = "";
	switch (tipo) {
	case TiposDeDesenho::FOGO: tipoEmTexto = "FOGO";
		break;
	case TiposDeDesenho::GELO: tipoEmTexto = "GELO";
		break;
	case TiposDeDesenho::AGUA: tipoEmTexto = "AGUA";
		break;
	case TiposDeDesenho::BURACO: tipoEmTexto = "BURACO";
		break;
	case TiposDeDesenho::MURO: tipoEmTexto = "MURO";
		break;
	case TiposDeDesenho::NUVEM: tipoEmTexto = "NUVEM";
		break;
	}
	return tipoEmTexto;
}


TiposDeDesenho::~TiposDeDesenho()
{
}
