#pragma once
#include "Contornos.h"
#include "Forma.h"

class ContornosParaDesenho :
	public Contornos
{
protected:
	void preprocessar(); // overload
	void filtrarArestas(); // overload
public:
	ContornosParaDesenho(Imagem * img);
	vector<vector<cv::Point>> getContornos(); // overload | Retorna apenas os contornos no n�vel mais alto da hierarquia.
	vector<int> indicesDosContornos(); // Retorna vetor com �ndices dos contornos no n�vel mais alto da hierarquia.
	vector<int> indicesDosContornosInternos(int indice); // Retorna �dices dos contornos internos ao controno de �ndice passado por par�metro.
	vector<Forma> formasInternas(int indice); // Retorna vetor com contornos inernos da forma.
	vector<Forma> formas(); // Retorna vetor com formas presentes nos contornos. 
	vector<Forma> formas_r(); // Vers�o r�pida da fun��o formas();
	~ContornosParaDesenho();
};

