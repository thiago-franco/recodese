#pragma once
#include "Filtro.h"
#include "Imagem.h"
#include <iostream>

using namespace std;

// Classe que possibilita a extra��o de contornos presentes em uma imagem encapsulando fun��es da biblioteca OpenCV.
class Contornos
{
protected:
	Filtro * arestas; // Guarda arestas usadas para detectar um contorno.
	vector<vector<cv::Point>>  * contornos; // Vetor de vetores de pontos que representam contornos.
	virtual void preprocessar(); // Prepara imagem para extra��o de arestas aplicando diferentes filtros. DEVE ALTERAR IMAGEM ORIGINAL.
	virtual void filtrarArestas(); // Prepara imagem com arestas extraidas para a detec��o de contornos. N�O DEVE ALTERAR IMAGEM ORIGINAL.
public:
	vector<cv::Vec4i> * hierarquia; // Guarda hierarquia seguida pelos contronos. 
	Contornos(Imagem * img);
	Filtro * getArestas();
	virtual vector<vector<cv::Point>> getContornos();
	void criarFiltro(Imagem * img); // Cria um filtro para a imagem recebida e armazena no atributo "arestas".
	void extrairArestas(int intensidade, int filtragem = 1); // Identifica arestas na imagem. "filtragem" indica o tipo de filtro a ser usado [1|2].
	void extrairContornos(bool hierarquico = true); // Extrai contornos da imagem e armazena no atributo "contornos".
	Imagem visualizarContornos(int niveis = 0, bool exibir = true); // Exibe contronos extraidos da imagem e retorna imagem contendo os mesmos.
	Imagem visualizarContornosNaImagem(int niveis = 0, bool exibir = true); // Exibe contornos sobrepostos � imagem da qual foram extra�dos. 
	vector<double> perimetros(); // Retorna vetor com per�metros dos contornos obtidos pela chamada de getContornos().
	vector<double> areas(); // Retorna vetor com �reas dos contornos obtidos pela chamada de getContornos().
	vector<cv::Moments> momentos(); // Retorna momentos dos contornos obtidos pela chamada de getContornos().
	vector<vector<double>> momentosHu(); // Retorna momentos de Hu dos contornos obtidos pela chamada de getContornos().
	vector<vector<cv::Point>> poligonosAproximados(float precisao = 0.02, bool debug = false); // Retorna pol�gonos que aproximam os contornos obtidos pela chamada de getContornos(). Degub permite visualiza��o de pol�gonos.
	vector<vector<cv::Vec4i>> defeitosDeConvexidade(); // Retorna pontos de defeito de convexidade dos contornos obtidos pela chamada de getContornos().
	vector<int> convexidades(); // Retorna vetor indicando se contornos obtidos pela chamada de getContornos() s�o convexos [1] ou n�o [0].
	vector<double> circulosMinimos(); // Retorna a �rea dos c�rculos m�nimos que circunscrevem os contornos obtidos pela chamada de getContornos().
	vector<double> melhoresElipses(); // Retorna a �rea das elipses que melhor aproximam os contornos obtidos pela chamada de getContornos().
	double perimetro(int indice); // Retorna per�metro do contorno de �ndice passado por par�metro.
	double area(int indice); // Retorna �rea do contorno de �ndice passado por par�metro.
	cv::Moments momento(int indice); // Retorna momentos do contorno de �ndice passado por par�metro.
	vector<double> momentoHu(int indice); // Retorna momentos de Hu do contorno de �ndice passado por par�metro.
	vector<cv::Point> poligonoAproximado(int indice, float precisao = 0.02); // Retorna pol�gono que aproxima o contorno de �ndice recebido por par�metro.
	vector<cv::Vec4i> defeitoDeConvexidade(int indice); // Retorna pontos de defeito de convexidade do contorno de �ndice passado por par�metro.
	vector<double> circuloMinimo(int indice); // Retorna �rea e centro do c�rculo m�nimo que circunscreve o contorno de �ndice passado por par�metro.
	static double perimetro(vector<cv::Point> contorno);  // Retorna per�metro do contorno passado por par�metro
	static double area(vector<cv::Point> contorno); // Retorna �rea do contorno passado por par�metro.
	static cv::Moments momento(vector<cv::Point> contorno); // Retorna momentos do contorno passado por par�metro.
	static vector<double> momentoHu(vector<cv::Point> contorno); // Retorna momentos de Hu do contorno passado por par�metro.
	static vector<cv::Point> poligonoAproximado(vector<cv::Point> contorno, float precisao = 0.02); // Retorna pol�gono que aproxima o contorno recebido por par�metro.
	static vector<cv::Vec4i> defeitoDeConvexidade(vector<cv::Point> contorno); // Retorna pontos de defeito de convexidade do contorno passado por par�metro.
	static vector<double> circuloMinimo(vector<cv::Point> contorno); // Retorna �rea e centro do c�rculo m�nimo que circunscreve o contorno passado por par�metro.
	static cv::Rect retangulo(vector<cv::Point> contorno); // Retorna o retangulo circunscrito ao contorno
	~Contornos();
};

