#include "Reconstrucao3DdeDesenhos.h"
#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

using namespace std;

Reconstrucao3DdeDesenhos::Reconstrucao3DdeDesenhos()
{
}

void Reconstrucao3DdeDesenhos::transformarCoordenadas(float vertices[][2], int n)
{
	float escalaX = 50.0f / 64.0f; //Usado para transformações de coordenadas em x do papel para a tela
	float escalaY = -35.0f / 48.0f; //Usado para transformações de coordenadas em y do papel para a tela
	for (int i = 0; i <= n; i++) {
		vertices[i][0] = vertices[i][0] * escalaX - 250;
		vertices[i][1] = vertices[i][1] * escalaY + 50;
	}
}

void Reconstrucao3DdeDesenhos::verticesDaDiagonalPrincipalDeUmRetangulo(float vertices[4][2], int * diagonal)
{
	float maiorDistancia = 0, distancia = 0;
	diagonal[0] = 0;
	for (int i = 0; i < 3; i++)
	{
		distancia = sqrt(pow((vertices[i][0] - vertices[0][0]), 2) + pow((vertices[i][1] - vertices[0][1]), 2));
		if (distancia > maiorDistancia)
		{
			maiorDistancia = distancia;
			diagonal[1] = i;
		}
	}
}

void Reconstrucao3DdeDesenhos::verticesDaDiagonalSecundariaDeUmRetangulo(int diagonal[2], int * diagonalSecundaria)
{
	for (int i = 0; i < 4; i++)
	{
		if (diagonal[0] != i && diagonal[1] != i)
			diagonalSecundaria[0] == 0 ? diagonalSecundaria[0] = i : diagonalSecundaria[1] = i;
	}
}

void Reconstrucao3DdeDesenhos::adjacenciasDasDiagonaisDeUmRetangulo(float vertices[4][2], int diagonalPrincipal[2], int diagonalSecundaria[2], int * adjPerto, int * adjLonge)
{
	float adjacencia1, adjacencia2;
	adjacencia1 = sqrt(pow((vertices[diagonalPrincipal[0]][0] - vertices[diagonalSecundaria[0]][0]), 2)
		+ pow(vertices[diagonalPrincipal[0]][1] - vertices[diagonalSecundaria[0]][1], 2));
	adjacencia2 = sqrt(pow((vertices[diagonalPrincipal[0]][0] - vertices[diagonalSecundaria[1]][0]), 2)
		+ pow(vertices[diagonalPrincipal[0]][1] - vertices[diagonalSecundaria[1]][1], 2));
	if (adjacencia1 <= adjacencia2)
	{
		adjPerto[0] = diagonalSecundaria[0];
		adjLonge[0] = diagonalSecundaria[1];
		adjPerto[1] = diagonalSecundaria[1];
		adjLonge[1] = diagonalSecundaria[0];
	}
	else
	{
		adjPerto[0] = diagonalSecundaria[1];
		adjLonge[0] = diagonalSecundaria[0];
		adjPerto[1] = diagonalSecundaria[0];
		adjLonge[1] = diagonalSecundaria[1];
	}
}

void Reconstrucao3DdeDesenhos::criarMuro(float vertices[][2], float altura)
{
	//glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	transformarCoordenadas(vertices, 4);

	int diagonal[2] = { 0, 0 };
	verticesDaDiagonalPrincipalDeUmRetangulo(vertices, diagonal);

	int repetidos[2] = { 0, 0 };
	verticesDaDiagonalSecundariaDeUmRetangulo(diagonal, repetidos);

	int adjPerto[2], adjLonge[2];
	adjacenciasDasDiagonaisDeUmRetangulo(vertices, diagonal, repetidos, adjPerto, adjLonge);

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0, 0, 0);
	glScalef(1, 1, 1);

	//glBegin(GL_QUADS);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f); //bottom
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], 0.0f);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], 0.0f);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura); //top
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], altura);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], altura);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(vertices[adjPerto[0]][0], vertices[adjPerto[0]][1], 0.0f);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(vertices[adjPerto[0]][0], vertices[adjPerto[0]][1], 0.0f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(vertices[adjPerto[1]][0], vertices[adjPerto[1]][1], 0.0f);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(vertices[adjPerto[1]][0], vertices[adjPerto[1]][1], 0.0f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(vertices[adjLonge[0]][0], vertices[adjLonge[0]][1], 0.0f);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(vertices[adjLonge[0]][0], vertices[adjLonge[0]][1], 0.0f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(vertices[adjLonge[1]][0], vertices[adjLonge[1]][1], 0.0f);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(vertices[adjLonge[1]][0], vertices[adjLonge[1]][1], 0.0f);
	
	glBegin(GL_TRIANGLES);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f); //bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura); //top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], altura);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], altura);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[adjPerto[0]][0], vertices[adjPerto[0]][1], 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(vertices[adjPerto[0]][0], vertices[adjPerto[0]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[adjPerto[0]][0], vertices[adjPerto[0]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[adjPerto[1]][0], vertices[adjPerto[1]][1], 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(vertices[adjPerto[1]][0], vertices[adjPerto[1]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[adjPerto[1]][0], vertices[adjPerto[1]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[adjLonge[0]][0], vertices[adjLonge[0]][1], 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(vertices[adjLonge[0]][0], vertices[adjLonge[0]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[adjLonge[0]][0], vertices[adjLonge[0]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[adjLonge[1]][0], vertices[adjLonge[1]][1], 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(vertices[adjLonge[1]][0], vertices[adjLonge[1]][1], 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(vertices[adjLonge[1]][0], vertices[adjLonge[1]][1], altura);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);

	glEnd();
	glPopMatrix();
}

void Reconstrucao3DdeDesenhos::criarRio(Vector2dVector vertices)
{	
	//Faz triangulação do polígono não convexo
	Vector2dVector poligonoTriangulado;
	Triangulate::Process(vertices, poligonoTriangulado);

	float escalaX = 50.0f / 64.0f; //Usado para transformações de coordenadas em x do papel para a tela
	float escalaY = -35.0f / 48.0f; //Usado para transformações de coordenadas em y do papel para a tela
	for (int i = 0; i < poligonoTriangulado.size(); i++) {
		poligonoTriangulado[i].Set(poligonoTriangulado[i].GetX() * escalaX - 250, poligonoTriangulado[i].GetY() * escalaY + 50);
	}

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0, 0, 0);
	glScalef(1, 1, 1);

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < poligonoTriangulado.size()/3; i++) {
		glVertex3f(poligonoTriangulado[i*3].GetX(), poligonoTriangulado[i*3].GetY(), 0.0f);
		glVertex3f(poligonoTriangulado[i*3+1].GetX(), poligonoTriangulado[i*3+1].GetY(), 0.0f);
		glVertex3f(poligonoTriangulado[i*3+2].GetX(), poligonoTriangulado[i*3+2].GetY(), 0.0f);
	}

	glEnd();
	glPopMatrix();
}

void Reconstrucao3DdeDesenhos::criarObjetoTeste()
{
	// CODIGO DO MURO 
	//glewExperimental = GL_TRUE;
	/*if (glewInit() != GLEW_OK)
	{
	std::cout << "Failed to initialize GLEW" << std::endl;
	}*/
	float vertices[4][2] = {
		{ 147, 339 },
		{ 159, 434 },
		{ 293, 428 },
		{ 277, 336 }
	};

	//trasformando coordenadas opencv para opengl
	float escalaX = 50.0f / 64.0f;
	float escalaY = -35.0f / 48.0f;

	vertices[0][0] = vertices[0][0] * escalaX - 250;
	vertices[1][0] = vertices[1][0] * escalaX - 250;
	vertices[2][0] = vertices[2][0] * escalaX - 250;
	vertices[3][0] = vertices[3][0] * escalaX - 250;
	vertices[0][1] = vertices[0][1] * escalaY + 50;
	vertices[1][1] = vertices[1][1] * escalaY + 50;
	vertices[2][1] = vertices[2][1] * escalaY + 50;
	vertices[3][1] = vertices[3][1] * escalaY + 50;

	// vertices de uma diagonal
	int diagonal[2];
	float maiorDistancia = 0, distancia = 0;
	diagonal[0] = 0;
	for (int i = 1; i <= 3; i++)
	{
		distancia = sqrt(pow((vertices[i][0] - vertices[0][0]), 2) + pow((vertices[i][1] - vertices[0][1]), 2));
		if (distancia > maiorDistancia)
		{
			maiorDistancia = distancia;
			diagonal[1] = i;
		}
	}

	int repetidos[2] = { 0, 0 };
	for (int i = 0; i < 4; i++)
	{
		if (diagonal[0] != i && diagonal[1] != i)
			repetidos[0] == 0 ? repetidos[0] = i : repetidos[1] = i;
	}

	//atribuindo adjacencias das diagonais
	int adjPerto[2], adjLonge[2];
	float adjacencia1, adjacencia2;
	adjacencia1 = sqrt(pow((vertices[diagonal[0]][0] - vertices[repetidos[0]][0]), 2)
		+ pow(vertices[diagonal[0]][1] - vertices[repetidos[0]][1], 2));
	adjacencia2 = sqrt(pow((vertices[diagonal[0]][0] - vertices[repetidos[1]][0]), 2)
		+ pow(vertices[diagonal[0]][1] - vertices[repetidos[1]][1], 2));
	if (adjacencia1 <= adjacencia2)
	{
		adjPerto[0] = repetidos[0];
		adjLonge[0] = repetidos[1];
		adjPerto[1] = repetidos[1];
		adjLonge[1] = repetidos[0];
	}
	else
	{
		adjPerto[0] = repetidos[1];
		adjLonge[0] = repetidos[0];
		adjPerto[1] = repetidos[0];
		adjLonge[1] = repetidos[1];
	}

	float altura = 100;
	float z = 1.5;

	glPushMatrix();
	glRotatef(0, 0, 0, 0);
	glTranslatef(0, 0, 0);
	glScalef(1, 1, 1);

	glBegin(GL_TRIANGLES);

	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f); //bottom
	glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], 0.0f);
	glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], 0.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);
	glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], 0.0f);
	glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], 0.0f);

	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura); //top
	glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], altura);
	glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], altura);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);
	glVertex3f(vertices[repetidos[0]][0], vertices[repetidos[0]][1], altura);
	glVertex3f(vertices[repetidos[1]][0], vertices[repetidos[1]][1], altura);

	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);
	glVertex3f(vertices[adjPerto[0]][0], vertices[adjPerto[0]][1], 0.0f);
	glVertex3f(vertices[adjPerto[0]][0], vertices[adjPerto[0]][1], 0.0f);
	glVertex3f(vertices[adjPerto[0]][0], vertices[adjPerto[0]][1], altura);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);

	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);
	glVertex3f(vertices[adjPerto[1]][0], vertices[adjPerto[1]][1], 0.0f);
	glVertex3f(vertices[adjPerto[1]][0], vertices[adjPerto[1]][1], 0.0f);
	glVertex3f(vertices[adjPerto[1]][0], vertices[adjPerto[1]][1], altura);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);

	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], 0.0f);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);
	glVertex3f(vertices[adjLonge[0]][0], vertices[adjLonge[0]][1], 0.0f);
	glVertex3f(vertices[adjLonge[0]][0], vertices[adjLonge[0]][1], 0.0f);
	glVertex3f(vertices[adjLonge[0]][0], vertices[adjLonge[0]][1], altura);
	glVertex3f(vertices[diagonal[0]][0], vertices[diagonal[0]][1], altura);

	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], 0.0f);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);
	glVertex3f(vertices[adjLonge[1]][0], vertices[adjLonge[1]][1], 0.0f);
	glVertex3f(vertices[adjLonge[1]][0], vertices[adjLonge[1]][1], 0.0f);
	glVertex3f(vertices[adjLonge[1]][0], vertices[adjLonge[1]][1], altura);
	glVertex3f(vertices[diagonal[1]][0], vertices[diagonal[1]][1], altura);

	glEnd();

	glPopMatrix();
}

Reconstrucao3DdeDesenhos::~Reconstrucao3DdeDesenhos()
{
}