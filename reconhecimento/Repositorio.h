#pragma once
#include "Forma.h"

// Interface para persistência de dados advindos de características extraídas de contornos.
class Repositorio
{
public:
	Repositorio();
	virtual void salvar(vector<Forma> d) = 0;
	virtual ~Repositorio();
};

