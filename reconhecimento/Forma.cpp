#include "Forma.h"
#include<string>

Forma::Forma(double p, double a)
{
	perimetro = p;
	area = a;
}

Forma::Forma(double p, double a, vector<double> m, vector<Forma> cint, char* t)
{
	perimetro = p;
	area = a;
	momentosHu = m;
	contornosInternos = cint;
	tipo = t;
}

string Forma::getTipo()
{
	return tipo;
}

int Forma::getX()
{
	return x;
}

int Forma::getY()
{
	return y;
}

vector<cv::Point> Forma::getPoligonoAproximado()
{
	return poligonoAproximado;
}

double Forma::getPerimetro()
{
	return perimetro;
}

double Forma::getArea()
{
	return area;
}

void Forma::setTipo(string t)
{
	tipo = t;
}

void Forma::setPerimetro(double p)
{
	perimetro = p;
}

void Forma::setArea(double a)
{
	area = a;
}

void Forma::setContornosInternos(vector<Forma> cint)
{
	contornosInternos = cint;
}

void Forma::setVerticesPoligonoAproximado(int v)
{
	verticesPoligonoAproximado = v;
}

void Forma::setDefeitosDeConvexidade(vector<double> d)
{
	defeitosDeConvexidade = d;
}

void Forma::setConvexo(int c)
{
	convexo = c;
}

void Forma::setAreaCirculo(double a)
{
	areaCirculo = a;
}

void Forma::setRetangulo(int r[4][2])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			retangulo[i][j] = r[i][j];
		}
	}
}

vector<double> Forma::getMomentosHu(bool escalar)
{
	if (!escalar)
		return momentosHu;
	else
	{
		vector<double> huEscalado(momentosHu.size());
		for (int i = 0; i < momentosHu.size(); i++)
		{
			huEscalado[i] = momentosHu[i] * 10000;
		}
		return huEscalado;
	}
}

int Forma::getVerticesPoligonoAproximado()
{
	return verticesPoligonoAproximado;
}

vector<double> Forma::getDefeitosDeConvexidade()
{
	return defeitosDeConvexidade;
}

int Forma::getConvexo()
{
	return convexo;
}

double Forma::getAreaCirculo()
{
	return areaCirculo;
}

vector<vector<int>> Forma::getRetangulo()
{
	vector<int> v1(retangulo[0][0], retangulo[0][1]), v2(retangulo[1][0], retangulo[1][1]), v3(retangulo[2][0], retangulo[2][1]), v4(retangulo[3][0], retangulo[3][1]);
	vector<vector<int>> v;
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);
	return v;
}

void Forma::setX(int px)
{
	x = px;
}

void Forma::setY(int py)
{
	y = py;
}

void Forma::setPoligonoAproximado(vector<cv::Point> poligono)
{
	poligonoAproximado = poligono;
}

double Forma::proporcaoAreaPerimetro()
{
	return area/perimetro;
}

int Forma::qtdContornosInternos()
{
	return contornosInternos.size();
}

double Forma::areaContornosInternos()
{
	double at = 0;
	for (int i = 0; i < contornosInternos.size(); i++)
	{
		at += contornosInternos[i].getArea();
	}
	return at;
}

double Forma::perimetroContornosInternos()
{
	double pt = 0;
	for (int i = 0; i < contornosInternos.size(); i++)
	{
		pt += contornosInternos[i].getPerimetro();
	}
	return pt;
}

double Forma::proporcaoAreaContornosInternos()
{
	double at, proporcao;
	at = areaContornosInternos();
	proporcao = area > 0 ? at / area : 0;
	return proporcao;
}

double Forma::proporcaoPerimetroContornosInternos()
{
	double pt, proporcao;
	pt = perimetroContornosInternos();
	proporcao = pt / perimetro;
	return proporcao;
}

double Forma::proporcaoContornosInternos()
{
	double proporcao, propContInt;
	propContInt = proporcaoPerimetroContornosInternos() != 0 ? 
		proporcaoAreaContornosInternos() / proporcaoPerimetroContornosInternos() : 0;
	proporcao = proporcaoAreaPerimetro() != 0 ? propContInt / proporcaoAreaPerimetro() : 0;
	return proporcao;
}

int Forma::qtdDefeitosDeConvexidade()
{
	return defeitosDeConvexidade.size();
}

double Forma::proporcaoDefeitosDeConvexidade()
{
	double defeitoTotal = 0;
	for (int i = 0; i < defeitosDeConvexidade.size(); i++)
	{
		defeitoTotal += defeitosDeConvexidade[i];
	}
	return defeitoTotal / perimetro;
}

double Forma::proporcaoCirculoMinimo()
{
	return areaCirculo > area ? (areaCirculo - area) / areaCirculo : 0;
}

// TODO: atualizar conforme mais características forem adicionadas
string Forma::caracteristicasEmTexto()
{
	vector<double> hu = getMomentosHu(true);
	string dados =
		to_string(static_cast<long double>(perimetro)) + ","
		+ to_string(static_cast<long double>(area)) + ","
		+ to_string(static_cast<long double>(proporcaoAreaPerimetro())) + ","
		+ to_string(static_cast<long long>(getVerticesPoligonoAproximado())) + ","
		+ to_string(static_cast<long long>(qtdDefeitosDeConvexidade())) + ","
		+ to_string(static_cast<long double>(proporcaoDefeitosDeConvexidade())) + ","
		+ to_string(static_cast<long long>(getConvexo())) + ","
		+ to_string(static_cast<long double>(proporcaoCirculoMinimo())) + ","
		+ to_string(static_cast<long long>(qtdContornosInternos())) + ","
		+ to_string(static_cast<long double>(proporcaoPerimetroContornosInternos())) + ","
		+ to_string(static_cast<long double>(proporcaoAreaContornosInternos())) + ","
		+ to_string(static_cast<long double>(proporcaoContornosInternos())) + ","
		+ to_string(static_cast<long double>(hu[0])) + ","
		+ to_string(static_cast<long double>(hu[1])) + ","
		+ to_string(static_cast<long double>(hu[2])) + ","
		+ to_string(static_cast<long double>(hu[3])) + ","
		+ to_string(static_cast<long double>(hu[4])) + ","
		+ to_string(static_cast<long double>(hu[5])) + ","
		+ to_string(static_cast<long double>(hu[6])) + ","
		+ tipo;
	return dados;
}

// TODO: manter consistência adicionando apenas características que são utilizadas no modelo de classificação
string Forma::caracteristicasEmTextoFormatado()
{
	vector<double> hu = getMomentosHu(true);
	string dados =
		//"perimetro:" + to_string(perimetro) + "," +
		//"area:" + to_string(area) + "," +
		"proporcao area perimetro:" + to_string(static_cast<long double>(proporcaoAreaPerimetro())) + "," +
		"vertices:" + to_string(static_cast<long long>(getVerticesPoligonoAproximado())) + "," +
		"defeitos:" + to_string(static_cast<long long>(qtdDefeitosDeConvexidade())) + "," +
		"proporcao defeitos:" + to_string(static_cast<long double>(proporcaoDefeitosDeConvexidade())) + "," +
		//"convexo:" + to_string(getConvexo()) + "," +
		"proporcao circulo minimo:" + to_string(static_cast<long double>(proporcaoCirculoMinimo())) + "," +
		"contornos internos:" + to_string(static_cast<long long>(qtdContornosInternos())) + "," +
		"proporcao perimetros internos:" + to_string(static_cast<long double>(proporcaoPerimetroContornosInternos())) + "," +
		"proporcao areas internas:" + to_string(static_cast<long double>(proporcaoAreaContornosInternos())) + "," +
		"proporcao contornos internos:" + to_string(static_cast<long double>(proporcaoContornosInternos())) + "," +
		"h1:" + to_string(static_cast<long double>(hu[0])) + "," +
		"h2:" + to_string(static_cast<long double>(hu[1])) + "," +
		"h3:" + to_string(static_cast<long double>(hu[2])) + "," +
		"h4:" + to_string(static_cast<long double>(hu[3])) + "," +
		"h5:" + to_string(static_cast<long double>(hu[4])) + "," +
		"h6:" + to_string(static_cast<long double>(hu[5])) + "," +
		"h7:" + to_string(static_cast<long double>(hu[6]));
	return dados;
}

// TODO: atualizar conforme mais características forem adicionadas
string Forma::caracteristicas()
{
	string caracteristicas = "perimetro,area,proporcao area perimetro,vertices,defeitos,proporcao defeitos,convexo,proporcao circulo minimo,contornos internos,proporcao perimetros internos,proporcao areas internas,proporcao contornos internos,h1,h2,h3,h4,h5,h6,h7,tipo";
	return caracteristicas;
}

void Forma::rotularFormas(vector<Forma> * formas, string tipo)
{
	for (int i = 0; i < formas->size(); i++)
	{
		formas->at(i).tipo = tipo;
	}
}

Forma::~Forma()
{
}
