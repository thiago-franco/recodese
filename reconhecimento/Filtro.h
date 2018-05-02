#pragma once
#include "Imagem.h"

// Classe que agrupa os principais filtros oferecidos pela boblioteca OpenCV.
class Filtro
{
private:
	Imagem * imgOriginal;
	Imagem * imgFiltrada;
public:
	Filtro();
	Filtro(Imagem * imagem);
	Imagem * getImgOriginal();
	Imagem * getImgFiltrada();
	void setImgOriginal(Imagem * img);
	void manterFiltro(); // Substitui a imagem original pela imagem filtrada.
	void blur(int intensidade); // Aplica filtro blur na imagem.
	void erodir(int intesidade); // Erode imagem.
	void dilatar(int intesidade); // Dilata imagem.
	void segmentar(int intensidade); 
	void negativo(); 
	void para8UC();
	void edges(int intensidade, bool visualizavel = true); // Aplica filtro para encontrar "arestas" na imagem.
	void cannyEdges(int intensidade, bool visualizavel = true); // Encontra "arestas" na imagem com o método de Canny.
	~Filtro();
};

