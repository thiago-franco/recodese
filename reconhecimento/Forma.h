#pragma once
#include <vector>
#include "Imagem.h"

using namespace std;

// Classe que agrupa caracter�sticas extra�das de um contorno.
class Forma
{
private:
	string tipo; // Especifica a classe de formas a qual o objeto pertence (ex. n�vem, fogo, buraco...).
	int x;
	int y;
	vector<cv::Point> poligonoAproximado;
	double perimetro;
	double area;
	vector<Forma> contornosInternos; // Contornos presentes no interior da forma.
	vector<double> momentosHu;
	int verticesPoligonoAproximado; // N�mero de v�rtices do pol�gono que aproxima a forma.
	vector<double> defeitosDeConvexidade; // Vetor com comprimentos de todos os defeitos de convexidade da forma.
	int convexo; // [1] se convexo [0] caso contr�rio.
	double areaCirculo; // �rea do menor c�rculo que circunscreve a forma.
	int retangulo[4][2]; // Ret�ngulo circunscrito na forma.
public:
	Forma(double periemtro, double area);
	Forma(double perimetro, double area, vector<double> momentosHu, vector<Forma> contornosInternos, char* tipo = "?");
	string getTipo();
	int getX();
	int getY();
	vector<cv::Point> getPoligonoAproximado();
	double getPerimetro();
	double getArea();
	vector<double> getMomentosHu(bool escalar = false); // Par�metro decide se valores ser�o dimensionados em escala melhor mensur�vel.
	int getVerticesPoligonoAproximado();
	vector<double> getDefeitosDeConvexidade();
	int getConvexo();
	double getAreaCirculo();
	vector<vector<int>> getRetangulo();
	void setTipo(string t);
	void setX(int px);
	void setY(int py);
	void setPoligonoAproximado(vector<cv::Point> poligono);
	void setPerimetro(double p);
	void setArea(double a);
	void setContornosInternos(vector<Forma> cint); 
	void setVerticesPoligonoAproximado(int v);
	void setDefeitosDeConvexidade(vector<double> d);
	void setConvexo(int c);
	void setAreaCirculo(double a);
	void setRetangulo(int retangulo[4][2]);
	double proporcaoAreaPerimetro(); // Retorna a raz�o entre �rea e per�metro da forma.
	int qtdContornosInternos(); // Retorna quantidade de contornos contidos no interior da fomra.
	double areaContornosInternos(); // Retorna �rea total ocupada pelos contornos internos � forma.
	double perimetroContornosInternos(); // Retorna somat�rio de per�metros de contornos internos da forma.
	double proporcaoAreaContornosInternos(); // Retorna a raz�o entre a �rea da forma e a �rea todas de seus contornos internos.
	double proporcaoPerimetroContornosInternos(); // Retorna a raz�o entre o per�metro da forma e o per�metro todas de seus contornos internos.
	double proporcaoContornosInternos(); // Retorna a raz�o entre a propor��o �rea/per�metro da forma e de seus contornos internos.
	int qtdDefeitosDeConvexidade(); // Retorna quantidade de defeitos de convexidade.
	double proporcaoDefeitosDeConvexidade(); // Retorna a raz�o entre comprimento total dos defeitos e per�metro da forma.
	double proporcaoCirculoMinimo(); // Retorna raz�o entre areas do circulo m�nimo e da forma.
	string caracteristicasEmTexto(); // Retorna caracteristicas da forma separadas por v�rgula em uma string.
	string caracteristicasEmTextoFormatado(); // Retorna caracteristicas da forma no formato [descricao1:valor1,descricao2:valor2,...,desscricaoN:valorN].
	static string caracteristicas(); // Retorna string com caracter�sticas atualmente acess�veis atrav�s da forma separadas por v�rgula.
	static void rotularFormas(vector<Forma> * formas, string tipo); // Recebe vetor de formas e as atribui o tipo recebido.
	~Forma();
};

