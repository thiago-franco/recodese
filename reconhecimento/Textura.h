#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <string>
using namespace std;

class Textura
{
private:
	static int qtdTexturasEmUso;
	int indiceTextura;
	GLuint textura;
public:
	Textura(string caminhoArquivo);
	void usar();
	GLuint getTextura();
	int getIndiceTextura();
	~Textura();
};

