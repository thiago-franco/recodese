#include "Imagem.h"
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Imagem::Imagem()
{
	nome = "Imagem";
}

Imagem::Imagem(string origem, bool vga)
{
	nome = "Imagem";
	caminho = origem;
	carregarImagem(origem, vga);
}

Imagem::Imagem(Mat imagem)
{
	nome = "Imagem";
	img = imagem;
}

string Imagem::getCaminho()
{
	return caminho;
}

Mat Imagem::getImagem()
{
	return img;
}

string Imagem::getNome()
{
	return nome;
}

void Imagem::setCamihno(string c)
{
	caminho = c;
}

void Imagem::setNome(string n)
{
	nome = n;
}

void Imagem::setImagem(Mat i)
{
	img = i;
}

bool Imagem::checarImagem()
{
	return img.empty() ? false : true;
}

void Imagem::carregarImagem(string c, bool vga)
{
	try
	{
		img = imread(c);
		if (vga)
		{
			redimensionar(640, 480);
		}
	}
	catch (Exception e)
	{
		cout << "Excecao ao carregar imagem: " << e.code << " " << e.err << endl;
	}
}

void Imagem::redimensionar(int x, int y)
{
	resize(img, img, Size(x, y));
}

Imagem Imagem::paraEscalaCinza()
{
	if (checarImagem())
	{
		if (img.channels() == 3) // checa se a imagem possui 3 canais (é RGB)
		{
			Mat imgCinza;
			cvtColor(img, imgCinza, CV_RGB2GRAY);
			Imagem imgConvertida(imgCinza);
			return imgConvertida;
		}
	}
	return img;
}

void Imagem::mostrarImagem()
{
	if (checarImagem()) {
		namedWindow(nome);
		imshow(nome, img);
	}
	else {
		cout << "Nao foi possivel mostrar imagem." << endl;
		system("pause");
	}
}

void Imagem::manterExibicao()
{
	waitKey(0);
}

void Imagem::encerrarExibicao()
{
	destroyAllWindows();
}

void Imagem::cirarJanela(string nome)
{
	namedWindow(nome);
}

Imagem::~Imagem()
{
	img.release();
}