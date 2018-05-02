#pragma once
#include <iostream>

using namespace std;

class TiposDeDesenho
{
public:
	enum { FOGO = 0, GELO = 1, AGUA = 2, BURACO = 3, MURO = 4, NUVEM = 5 };
	TiposDeDesenho();
	static int quantidadeDeTipos(); // Retorna a quantidade de tipos existenstes.
	static string emString(int tipo); // Retorna o texto equivalente ao tipo recebido por parâmetro.
	~TiposDeDesenho();
};

