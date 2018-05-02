#pragma once
#include "Triangulate.h"

class Reconstrucao3DdeDesenhos
{
public:
	Reconstrucao3DdeDesenhos();
	void criarMuro(float retangulo[][2], float altura = 100);
	void criarRio(Vector2dVector vertices);
	void criarObjetoTeste();
	~Reconstrucao3DdeDesenhos();
private:
	void transformarCoordenadas(float vertices[][2], int n);
	void verticesDaDiagonalPrincipalDeUmRetangulo(float vertices[4][2], int * diagonal);
	void verticesDaDiagonalSecundariaDeUmRetangulo(int diagonal[2], int * diagonalSecundaria);
	void adjacenciasDasDiagonaisDeUmRetangulo(float vertices[4][2], int diagonalPrincipal[2], int diagonalSecundaria[2], int * proximos, int * distantes);
};

