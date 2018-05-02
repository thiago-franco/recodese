#include "Contornos.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;

Contornos::Contornos(Imagem * img)
{
	criarFiltro(img);
	contornos = new vector<vector<cv::Point>>();
	hierarquia = new vector<cv::Vec4i>();
}

Filtro * Contornos::getArestas()
{
	return arestas;
}

vector<vector<Point>> Contornos::getContornos()
{
	return *contornos;
}

void Contornos::criarFiltro(Imagem * img)
{
	Filtro * f = new Filtro(img);
	arestas = f;
}

void Contornos::preprocessar()
{
	cout << "Preprocessamento generico" << endl;
	arestas->blur(1);
	arestas->manterFiltro();
}

void Contornos::filtrarArestas()
{
	cout << "Filtragem generica de arestas" << endl;
}

void Contornos::extrairArestas(int intensidade, int filtragem)
{
	Imagem * original = arestas->getImgOriginal();
	preprocessar(); // subclasses terão implementação específica 
	switch (filtragem)
	{
	case 1: arestas->cannyEdges(intensidade/3, false); // escalando intensidade por 3 pois filtro canny é mais sensível
		break;
	case 2: arestas->edges(intensidade);
		break;
	default: 
		cout << "Não foi possível filtrar arestas." << endl;
		break;
	}
	arestas->setImgOriginal(original);
}

void Contornos::extrairContornos(bool hierarquico)
{
	if (!arestas->getImgFiltrada()->checarImagem())
	{
		cout << "Nao foi possivel extrair contornos pois arestas da imagem ainda nao foram filtradas." << endl;
		return;
	}
	filtrarArestas(); // subclasses terão implementação específica 
	if (!(*hierarquia).empty())
		(*hierarquia).clear();
	if (hierarquico)
		findContours(arestas->getImgFiltrada()->getImagem(), *contornos, *hierarquia, RETR_TREE, CV_CHAIN_APPROX_NONE);
	else
		findContours(arestas->getImgFiltrada()->getImagem(), *contornos, RETR_LIST, CV_CHAIN_APPROX_NONE);
}

Imagem Contornos::visualizarContornos(int niveis, bool exibir)
{
	Mat img;
	if ((*contornos).empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		Imagem imgContornos(img);
		return imgContornos;
	}
	img.create(arestas->getImgOriginal()->getImagem().size(), arestas->getImgOriginal()->getImagem().type());
	img = Scalar::all(0);
	if ((*hierarquia).empty() || niveis == 0)
	{
		drawContours(img, *contornos, -1, Scalar(0, 0, 255));
	}
	else
	{
		drawContours(img, *contornos, -1, Scalar(0, 0, 255), 1, 8, *hierarquia, niveis);
	}
	if (exibir)
	{
		namedWindow("Contornos");
		imshow("Contornos", img);
	}
	
	Imagem imgContornos(img);
	imgContornos.setNome("Contornos");
	return imgContornos;
}

Imagem Contornos::visualizarContornosNaImagem(int niveis, bool exibir)
{
	Mat img;
	if ((*contornos).empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		Imagem imgContornos(img);
		return imgContornos;
	}
	img = arestas->getImgOriginal()->getImagem().clone();
	if ((*hierarquia).empty() || niveis == 0)
	{
		drawContours(img, *contornos, -1, Scalar(0, 0, 255));
		
	}
	else
	{
		drawContours(img, *contornos, -1, Scalar(0, 0, 255), 1, 8, *hierarquia, niveis);
	}
	if (exibir)
	{
		namedWindow("Contornos na imagem");
		imshow("Contornos na imagem", img);
	}
	Imagem imgContornos(img);
	imgContornos.setNome("Contornos na imagem");
	return imgContornos;
}

vector<double> Contornos::perimetros()
{
	vector<vector<Point>> contornos = getContornos();
	vector<double> p(contornos.size());
	if (contornos.empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return p;
	}
	for (int i = 0; i < contornos.size(); i++)
	{
		vector<Point> contorno = contornos[i];
		p[i] = arcLength(contorno, true);
	}
	return p;
}

vector<double> Contornos::areas()
{
	vector<vector<Point>> contornos = getContornos();
	vector<double> a(contornos.size());
	if (contornos.empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return a;
	}
	for (int i = 0; i < contornos.size(); i++)
	{
		vector<Point> contorno = contornos[i];
		a[i] = contourArea(contorno);
	}
	return a;
}

vector<Moments> Contornos::momentos()
{
	vector<vector<Point>> contornos = getContornos();
	vector<Moments> m(contornos.size());
	if (contornos.empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return m;
	}
	for (int i = 0; i < contornos.size(); i++)
	{
		m[i] = moments(contornos[i], false);
	}
	return m;
}

vector<vector<double>> Contornos::momentosHu()
{
	vector<Moments> m = momentos();
	vector<vector<double>> mu(m.size());
	if ((*contornos).empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return mu;
	}
	for (int i = 0; i < m.size(); i++)
	{
		vector<double> hu(7);
		HuMoments(m[i], hu);
		mu[i] = hu;
	}
	return mu;
}

vector<vector<Point>> Contornos::poligonosAproximados(float precisao, bool debug)
{
	vector<vector<Point>> contornos = getContornos(), poligonos(contornos.size());
	if (contornos.empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return poligonos;
	}
	for (int i = 0; i < contornos.size(); i++)
	{
		vector<Point> contorno = contornos[i], poligono;
		float epsilon = precisao*arcLength(contorno, true);
		approxPolyDP(contorno, poligono, epsilon, true);
		poligonos[i] = poligono;
	}
	if (debug) {
		Mat img = arestas->getImgOriginal()->getImagem().clone();
		drawContours(img, poligonos, -1, Scalar(0, 0, 255));
		imshow("Debug: Poligonos Aproximados", img);
		Imagem::manterExibicao();
	}
	return poligonos;
}

vector<vector<Vec4i>> Contornos::defeitosDeConvexidade()
{
	vector<vector<Point>> contornos = getContornos();
	vector<vector<Vec4i>> defeitos(contornos.size());
	if (contornos.empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return defeitos;
	}
	for (int i = 0; i < contornos.size(); i++)
	{
		vector<Point> contorno = contornos[i];
		vector<int> hull;
		vector<Vec4i> defs;
		try 
		{
			convexHull(contorno, hull, false, false);
			convexityDefects(contorno, hull, defs);
			defeitos[i] = defs;
		}
		catch (Exception e)
		{
			cout << e.err;
		}
		
	}
	return defeitos;
}

// TODO: verificar funcionamento (retornou 0 em todos os casos de teste)
vector<int> Contornos::convexidades()
{
	vector<vector<Point>> contornos = getContornos();
	vector<int> convexos(contornos.size());
	if (contornos.empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return convexos;
	}
	for (int i = 0; i < contornos.size(); i++)
	{
		vector<Point> contorno = contornos[i];
		int eConvexo;
		eConvexo = isContourConvex(contorno) ? 1 : 0;
		convexos[i] = eConvexo;
	}
	return convexos;
}

vector<double> Contornos::circulosMinimos()
{
	vector<vector<Point>> contornos = getContornos();
	vector<double> circulos(contornos.size());
	if (contornos.empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return circulos;
	}
	for (int i = 0; i < contornos.size(); i++)
	{
		vector<Point> contorno = contornos[i];
		Point2f centro;
		float raio;
		double area;
		minEnclosingCircle(contorno, centro, raio);
		area = CV_PI*pow(raio, 2);
		circulos[i] = area;
	}
	return circulos;
}

vector<double> Contornos::melhoresElipses()
{
	vector<vector<Point>> contornos = getContornos();
	vector<double> elipses(contornos.size());
	if (contornos.empty())
	{
		cout << "Contornos ainda nao foram extraidos." << endl;
		return elipses;
	}
	for (int i = 0; i < contornos.size(); i++)
	{
		RotatedRect elipse = fitEllipse(contornos[i]);
		// TODO: terminar extração de área das elipses
	}
}

double Contornos::perimetro(int indice)
{
	double p = 0;
	vector<Point> contorno = (*contornos)[indice];
	if (!contorno.size() > 0)
	{
		cout << "Nenhum contorno encontrado para o índice " << indice << endl;
		return 0.0;
	}
	return perimetro(contorno);
}

double Contornos::area(int indice)
{
	double a = 0;
	vector<Point> contorno = (*contornos)[indice];
	if (!contorno.size() > 0)
	{
		cout << "Nenhum contorno encontrado para o índice " << indice << endl;
		return 0.0;
	}
	return area(contorno);
}

cv::Moments Contornos::momento(int indice)
{
	vector<Point> contorno = (*contornos)[indice];
	if (!contorno.size() > 0)
	{
		cout << "Nenhum contorno encontrado para o índice " << indice << endl;
	}
	return momento(contorno);
}

vector<double> Contornos::momentoHu(int indice)
{
	vector<Point> contorno = (*contornos)[indice];
	if (!contorno.size() > 0)
	{
		cout << "Nenhum contorno encontrado para o índice " << indice << endl;
	}
	return momentoHu(contorno);
}

vector<cv::Point> Contornos::poligonoAproximado(int indice, float precisao)
{
	vector<Point> contorno = (*contornos)[indice], poligono(contorno.size());
	if (!contorno.size() > 0)
	{
		cout << "Nenhum contorno encontrado para o índice " << indice << endl;
	}
	return poligonoAproximado(contorno);
}

vector<cv::Vec4i> Contornos::defeitoDeConvexidade(int indice)
{
	if (!(*contornos)[indice].size() > 0)
	{
		cout << "Nenhum contorno encontrado para o índice " << indice << endl;
	}
	return defeitoDeConvexidade((*contornos)[indice]);
}

vector<double> Contornos::circuloMinimo(int indice)
{
	vector<Point> contorno = (*contornos)[indice];
	if (!contorno.size() > 0)
	{
		cout << "Nenhum contorno encontrado para o índice " << indice << endl;
	}
	return circuloMinimo(contorno);
}

double Contornos::perimetro(vector<Point> contorno)
{
	double p = 0;
	p = arcLength(contorno, true);
	return p;
}

double Contornos::area(vector<Point> contorno)
{
	double a = 0;
	a = contourArea(contorno);
	return a;
}

cv::Moments Contornos::momento(vector<Point> contorno)
{
	Moments m = moments(contorno, false);
	return m;
}

vector<double> Contornos::momentoHu(vector<cv::Point> contorno)
{
	Moments m = momento(contorno);
	vector<double> hu(7);
	HuMoments(m, hu);
	return hu;
}

vector<cv::Point> Contornos::poligonoAproximado(vector<cv::Point> contorno, float precisao)
{
	vector<Point> poligono(contorno.size());
	float epsilon = precisao*arcLength(contorno, true);
	approxPolyDP(contorno, poligono, epsilon, true);
	return poligono;
}

vector<cv::Vec4i> Contornos::defeitoDeConvexidade(vector<cv::Point> contorno)
{
	vector<cv::Point> hull(contorno.size());
	vector<int> hullIds(contorno.size());
	vector<cv::Vec4i> defs(contorno.size()); 
	try
	{
		convexHull(contorno, hull, false, false);
		convexHull(contorno, hullIds, false, false);
		if (hullIds.size() > 3) {
			convexityDefects(contorno, hullIds, defs);
		}
	}
	catch (Exception e)
	{
		cout << "Erro em defeito de convexidade: " << e.err;
	}
	return defs;
}

vector<double> Contornos::circuloMinimo(vector<cv::Point> contorno)
{
	Point2f centro;
	float raio;
	double area;
	minEnclosingCircle(contorno, centro, raio);
	area = CV_PI*pow(raio, 2);
	double circulo[] = { area, centro.x, centro.y };
	vector<double> circuloVec(circulo, circulo + 3);
	return circuloVec;
}

cv::Rect Contornos::retangulo(vector<cv::Point> contorno)
{
	return cv::boundingRect(contorno);
}

Contornos::~Contornos()
{
	delete(arestas);
}
