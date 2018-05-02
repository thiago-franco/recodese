#pragma once
#include "Forma.h"

class ClienteDeClassificacao
{
private: 
	string host;
	int porta;
	int pacotes;
	char fim;
public:
	ClienteDeClassificacao();
	string getHost();
	int getPorta();
	int getPacotes();
	char getFim();
	int requisitarClassificacao(Forma * forma, bool debug = false); // Solicita classificação da forma ao servidor.
	int requisitarClassificacao(string caracteristicasFormatadas, bool debug = false);
	~ClienteDeClassificacao();
};
