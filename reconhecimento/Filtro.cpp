#include "Filtro.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Filtro::Filtro()
{
	imgOriginal = new Imagem();
	imgFiltrada = new Imagem();
}

Filtro::Filtro(Imagem * imagem)
{
	imagem->setNome("Imagem Original");
	imgOriginal = imagem;
	imgFiltrada = new Imagem();
}

Imagem * Filtro::getImgOriginal()
{
	return imgOriginal;
}

Imagem * Filtro::getImgFiltrada()
{
	if (!imgFiltrada->checarImagem())
	{
		cout << "Nenhum filtro foi aplicado ainda." << endl;
		system("pause");
	}
	return imgFiltrada;
}

void Filtro::setImgOriginal(Imagem * img)
{
	imgOriginal = img;
	imgOriginal->setNome("Imagem Original");
}

void Filtro::manterFiltro()
{
	imgOriginal = getImgFiltrada();
}

void Filtro::blur(int intensidade)
{
	if (imgOriginal->checarImagem())
	{
		// Parâmetros para função GuassianBlur não podem ser pares.
		intensidade = intensidade % 2 == 0 ? intensidade + 1 : intensidade;
		Mat original = imgOriginal->getImagem();
		Mat filtrada;
		GaussianBlur(original, filtrada, Size(intensidade, intensidade), 0.3*intensidade);
		imgFiltrada->setImagem(filtrada);
		string nome = imgOriginal->getNome();
		nome += " Blur";
		imgFiltrada->setNome(nome);
	}
	else
	{
		cout << "Filtro blur nao aplicado corretamente." << endl;
	}
}

void Filtro::erodir(int intensidade)
{
	if (imgOriginal->checarImagem())
	{
		// Parâmetros para função erode não podem ser pares.
		intensidade = intensidade % 2 == 0 ? intensidade + 1 : intensidade;
		Mat original = imgOriginal->getImagem();
		Mat filtrada;
		Mat kernel = getStructuringElement(MORPH_RECT, Size(intensidade, intensidade));
		erode(original, filtrada, kernel);
		imgFiltrada->setImagem(filtrada);
		string nome = imgOriginal->getNome();
		nome += " Erodida";
		imgFiltrada->setNome(nome);
	}
	else
	{
		cout << "Filtro erodir nao aplicado corretamente." << endl;
	}
}

void Filtro::dilatar(int intensidade)
{
	if (imgOriginal->checarImagem())
	{
		// Parâmetros para função GuassianBlur não podem ser pares.
		intensidade = intensidade % 2 == 0 ? intensidade + 1 : intensidade;
		Mat original = imgOriginal->getImagem();
		Mat filtrada;
		Mat kernel = getStructuringElement(MORPH_RECT, Size(intensidade, intensidade));
		dilate(original, filtrada, kernel);
		imgFiltrada->setImagem(filtrada);
		string nome = imgOriginal->getNome();
		nome += " Dilatada";
		imgFiltrada->setNome(nome);
	}
	else
	{
		cout << "Filtro dilatar nao aplicado corretamente." << endl;
	}
}

void Filtro::segmentar(int intensidade)
{
	if (imgOriginal->checarImagem())
	{	
		Mat cinza = imgOriginal->paraEscalaCinza().getImagem();
		Mat simg;
		threshold(cinza, simg, intensidade, 255, 0);
		imgFiltrada->setImagem(simg);
		string nome = imgOriginal->getNome();
		nome += " Segmentada";
		imgFiltrada->setNome(nome);
	}
	else
	{
		cout << "Filtro segmentar nao aplicado corretamente." << endl;
	}
}

void Filtro::negativo()
{
	if (imgOriginal->checarImagem())
	{
		Mat negativo;
		negativo = 255 - imgOriginal->getImagem();
		imgFiltrada->setImagem(negativo);
		string nome = imgOriginal->getNome();
		nome += " Negativo";
		imgFiltrada->setNome(nome);
	}
	else
	{
		cout << "Filtro negativo nao aplicado corretamente." << endl;
	}
}

void Filtro::para8UC()
{
	Mat convertida;
	imgOriginal->getImagem().convertTo(convertida, CV_8UC1);
	imgFiltrada->setImagem(convertida);
}

void Filtro::edges(int intensidade, bool visualizavel)
{
	if (imgOriginal->checarImagem())
	{
		// Para detecção de arestas, imagem precisa ser em escala de cinza.
		Mat originalCinza = imgOriginal->paraEscalaCinza().getImagem();
		// Cálculo de gradientes 
		Mat grad, gradX, gradY;
		Scharr(originalCinza, gradX, CV_32F, 1, 0);
		Scharr(originalCinza, gradY, CV_32F, 0, 1);
		cv::pow(gradX, 2, gradX);
		cv::pow(gradY, 2, gradY);
		grad = gradX + gradY;
		cv::sqrt(grad, grad);
		Mat edges;
		grad.convertTo(edges, CV_8UC1); // converte para 8 bits
		threshold(edges, edges, intensidade, 255, THRESH_TOZERO);
		imgFiltrada->setImagem(edges);
		string nome = imgOriginal->getNome();
		nome += " Arestas";
		imgFiltrada->setNome(nome);
	}
	else
	{
		cout << "Filtro edges nao aplicado corretamente." << endl;
	}
}

void Filtro::cannyEdges(int intensidade, bool visualizavel)
{
	if (imgOriginal->checarImagem())
	{
		// Para detecção de arestas, imagem precisa ser em escala de cinza.
		Mat originalCinza = imgOriginal->paraEscalaCinza().getImagem();		
		Canny(originalCinza, originalCinza, intensidade, intensidade * 3);
		if (visualizavel)
		{
			Mat filtrada;
			filtrada.create(imgOriginal->getImagem().size(), imgOriginal->getImagem().type());
			filtrada = Scalar::all(0);
			imgOriginal->getImagem().copyTo(filtrada, originalCinza);
			imgFiltrada->setImagem(filtrada);
		}
		else
		{ 
			imgFiltrada->setImagem(originalCinza);
		}
		string nome = imgOriginal->getNome();
		nome += " Arestas Canny";
		imgFiltrada->setNome(nome);
	}
	else
	{
		cout << "Filtro Canny edges não aplicado corretamente." << endl;
	}
}

Filtro::~Filtro()
{
	delete(imgOriginal);
	delete(imgFiltrada);
}