#pragma once
#include <vector>
#include "Imagem.h"

using namespace std;

// Classe que agrupa características extraídas de um contorno.
class Forma
{
private:
	string tipo; // Especifica a classe de formas a qual o objeto pertence (ex. núvem, fogo, buraco...).
	int x;
	int y;
	vector<cv::Point> poligonoAproximado;
	double perimetro;
	double area;
	vector<Forma> contornosInternos; // Contornos presentes no interior da forma.
	vector<double> momentosHu;
	int verticesPoligonoAproximado; // Número de vértices do polígono que aproxima a forma.
	vector<double> defeitosDeConvexidade; // Vetor com comprimentos de todos os defeitos de convexidade da forma.
	int convexo; // [1] se convexo [0] caso contrário.
	double areaCirculo; // Área do menor círculo que circunscreve a forma.
	int retangulo[4][2]; // Retângulo circunscrito na forma.
public:
	Forma(double periemtro, double area);
	Forma(double perimetro, double area, vector<double> momentosHu, vector<Forma> contornosInternos, char* tipo = "?");
	string getTipo();
	int getX();
	int getY();
	vector<cv::Point> getPoligonoAproximado();
	double getPerimetro();
	double getArea();
	vector<double> getMomentosHu(bool escalar = false); // Parâmetro decide se valores serão dimensionados em escala melhor mensurável.
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
	double proporcaoAreaPerimetro(); // Retorna a razão entre área e perímetro da forma.
	int qtdContornosInternos(); // Retorna quantidade de contornos contidos no interior da fomra.
	double areaContornosInternos(); // Retorna área total ocupada pelos contornos internos à forma.
	double perimetroContornosInternos(); // Retorna somatório de perímetros de contornos internos da forma.
	double proporcaoAreaContornosInternos(); // Retorna a razão entre a área da forma e a área todas de seus contornos internos.
	double proporcaoPerimetroContornosInternos(); // Retorna a razão entre o perímetro da forma e o perímetro todas de seus contornos internos.
	double proporcaoContornosInternos(); // Retorna a razão entre a proporção área/perímetro da forma e de seus contornos internos.
	int qtdDefeitosDeConvexidade(); // Retorna quantidade de defeitos de convexidade.
	double proporcaoDefeitosDeConvexidade(); // Retorna a razão entre comprimento total dos defeitos e perímetro da forma.
	double proporcaoCirculoMinimo(); // Retorna razão entre areas do circulo mínimo e da forma.
	string caracteristicasEmTexto(); // Retorna caracteristicas da forma separadas por vírgula em uma string.
	string caracteristicasEmTextoFormatado(); // Retorna caracteristicas da forma no formato [descricao1:valor1,descricao2:valor2,...,desscricaoN:valorN].
	static string caracteristicas(); // Retorna string com características atualmente acessíveis através da forma separadas por vírgula.
	static void rotularFormas(vector<Forma> * formas, string tipo); // Recebe vetor de formas e as atribui o tipo recebido.
	~Forma();
};

