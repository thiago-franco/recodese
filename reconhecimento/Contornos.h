#pragma once
#include "Filtro.h"
#include "Imagem.h"
#include <iostream>

using namespace std;

// Classe que possibilita a extração de contornos presentes em uma imagem encapsulando funções da biblioteca OpenCV.
class Contornos
{
protected:
	Filtro * arestas; // Guarda arestas usadas para detectar um contorno.
	vector<vector<cv::Point>>  * contornos; // Vetor de vetores de pontos que representam contornos.
	virtual void preprocessar(); // Prepara imagem para extração de arestas aplicando diferentes filtros. DEVE ALTERAR IMAGEM ORIGINAL.
	virtual void filtrarArestas(); // Prepara imagem com arestas extraidas para a detecção de contornos. NÃO DEVE ALTERAR IMAGEM ORIGINAL.
public:
	vector<cv::Vec4i> * hierarquia; // Guarda hierarquia seguida pelos contronos. 
	Contornos(Imagem * img);
	Filtro * getArestas();
	virtual vector<vector<cv::Point>> getContornos();
	void criarFiltro(Imagem * img); // Cria um filtro para a imagem recebida e armazena no atributo "arestas".
	void extrairArestas(int intensidade, int filtragem = 1); // Identifica arestas na imagem. "filtragem" indica o tipo de filtro a ser usado [1|2].
	void extrairContornos(bool hierarquico = true); // Extrai contornos da imagem e armazena no atributo "contornos".
	Imagem visualizarContornos(int niveis = 0, bool exibir = true); // Exibe contronos extraidos da imagem e retorna imagem contendo os mesmos.
	Imagem visualizarContornosNaImagem(int niveis = 0, bool exibir = true); // Exibe contornos sobrepostos à imagem da qual foram extraídos. 
	vector<double> perimetros(); // Retorna vetor com perímetros dos contornos obtidos pela chamada de getContornos().
	vector<double> areas(); // Retorna vetor com áreas dos contornos obtidos pela chamada de getContornos().
	vector<cv::Moments> momentos(); // Retorna momentos dos contornos obtidos pela chamada de getContornos().
	vector<vector<double>> momentosHu(); // Retorna momentos de Hu dos contornos obtidos pela chamada de getContornos().
	vector<vector<cv::Point>> poligonosAproximados(float precisao = 0.02, bool debug = false); // Retorna polígonos que aproximam os contornos obtidos pela chamada de getContornos(). Degub permite visualização de polígonos.
	vector<vector<cv::Vec4i>> defeitosDeConvexidade(); // Retorna pontos de defeito de convexidade dos contornos obtidos pela chamada de getContornos().
	vector<int> convexidades(); // Retorna vetor indicando se contornos obtidos pela chamada de getContornos() são convexos [1] ou não [0].
	vector<double> circulosMinimos(); // Retorna a área dos círculos mínimos que circunscrevem os contornos obtidos pela chamada de getContornos().
	vector<double> melhoresElipses(); // Retorna a área das elipses que melhor aproximam os contornos obtidos pela chamada de getContornos().
	double perimetro(int indice); // Retorna perímetro do contorno de índice passado por parâmetro.
	double area(int indice); // Retorna área do contorno de índice passado por parâmetro.
	cv::Moments momento(int indice); // Retorna momentos do contorno de índice passado por parâmetro.
	vector<double> momentoHu(int indice); // Retorna momentos de Hu do contorno de índice passado por parâmetro.
	vector<cv::Point> poligonoAproximado(int indice, float precisao = 0.02); // Retorna polígono que aproxima o contorno de índice recebido por parâmetro.
	vector<cv::Vec4i> defeitoDeConvexidade(int indice); // Retorna pontos de defeito de convexidade do contorno de índice passado por parâmetro.
	vector<double> circuloMinimo(int indice); // Retorna área e centro do círculo mínimo que circunscreve o contorno de índice passado por parâmetro.
	static double perimetro(vector<cv::Point> contorno);  // Retorna perímetro do contorno passado por parâmetro
	static double area(vector<cv::Point> contorno); // Retorna área do contorno passado por parâmetro.
	static cv::Moments momento(vector<cv::Point> contorno); // Retorna momentos do contorno passado por parâmetro.
	static vector<double> momentoHu(vector<cv::Point> contorno); // Retorna momentos de Hu do contorno passado por parâmetro.
	static vector<cv::Point> poligonoAproximado(vector<cv::Point> contorno, float precisao = 0.02); // Retorna polígono que aproxima o contorno recebido por parâmetro.
	static vector<cv::Vec4i> defeitoDeConvexidade(vector<cv::Point> contorno); // Retorna pontos de defeito de convexidade do contorno passado por parâmetro.
	static vector<double> circuloMinimo(vector<cv::Point> contorno); // Retorna área e centro do círculo mínimo que circunscreve o contorno passado por parâmetro.
	static cv::Rect retangulo(vector<cv::Point> contorno); // Retorna o retangulo circunscrito ao contorno
	~Contornos();
};

