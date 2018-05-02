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
	vector<vector<cv::Point>> getContornos(); // overload | Retorna apenas os contornos no nível mais alto da hierarquia.
	vector<int> indicesDosContornos(); // Retorna vetor com índices dos contornos no nível mais alto da hierarquia.
	vector<int> indicesDosContornosInternos(int indice); // Retorna ídices dos contornos internos ao controno de índice passado por parâmetro.
	vector<Forma> formasInternas(int indice); // Retorna vetor com contornos inernos da forma.
	vector<Forma> formas(); // Retorna vetor com formas presentes nos contornos. 
	vector<Forma> formas_r(); // Versão rápida da função formas();
	~ContornosParaDesenho();
};

