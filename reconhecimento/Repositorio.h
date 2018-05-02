#pragma once
#include "Forma.h"

// Interface para persist�ncia de dados advindos de caracter�sticas extra�das de contornos.
class Repositorio
{
public:
	Repositorio();
	virtual void salvar(vector<Forma> d) = 0;
	virtual ~Repositorio();
};

