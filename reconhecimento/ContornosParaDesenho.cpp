#include "ContornosParaDesenho.h"

using namespace cv;

ContornosParaDesenho::ContornosParaDesenho(Imagem * img) : Contornos(img)
{
}

void ContornosParaDesenho::preprocessar()
{
	//cout << "Prepocessamento de Desenho" << endl;
	arestas->blur(1);
	arestas->manterFiltro();
}

void ContornosParaDesenho::filtrarArestas()
{
	//cout << "Filtragem de arestas de desenhos" << endl;
	Imagem * original = arestas->getImgOriginal();
	original->setNome("Imagem Original");
	arestas->manterFiltro();
	arestas->erodir(1);
	arestas->manterFiltro();
	arestas->dilatar(3);
	arestas->setImgOriginal(original);
}

vector<vector<Point>> ContornosParaDesenho::getContornos()
{
	if ((*hierarquia).empty())
	{
		cout << "Contornos ainda nao extraidos ou extraidos de forma nao hierarquica";
	}
	vector<vector<Point>> v;
	vector<Point> contorno;
	int i = 0;
	while (i >= 0)
	{
		contorno = (*contornos)[i];
		if ((*hierarquia)[i][3] < 0) // Checa se contorno está no nível mais alto da (*hierarquia)
		{
			v.push_back(contorno);
			i = (*hierarquia)[i][0];
		}
		else
		{
			i = (*hierarquia)[i][3];
		}
	}
	return v;
}

vector<int> ContornosParaDesenho::indicesDosContornos()
{
	if ((*hierarquia).empty())
	{
		cout << "Contornos ainda nao extraidos ou extraidos de forma nao hierarquica";
	}
	vector<int> indices;
	int i = 0;
	while (i >= 0)
	{
		if ((*hierarquia)[i][3] < 0) // Checa se contorno está no nível mais alto da (*hierarquia)
		{
			indices.push_back(i);
			i = (*hierarquia)[i][0];
		}
		else
		{
			i = (*hierarquia)[i][3];
		}
	}
	return indices;
}

vector<int> ContornosParaDesenho::indicesDosContornosInternos(int indice)
{
	vector<int> indices;
	if ((*hierarquia).empty())
	{
		cout << "Contornos ainda nao extraidos ou extraidos de forma nao hierarquica";
	}
	int i;
	if ((*hierarquia)[indice][2] >= 0)
	{
		i = (*hierarquia)[indice][2];
		while ((*hierarquia)[i][0] >= 0)
		{
			indices.push_back(i);
			i = (*hierarquia)[i][0];
		}
	}
	return indices;
}

vector<Forma> ContornosParaDesenho::formasInternas(int indice)
{
	vector<Forma> cint;
	vector<int> indices = indicesDosContornosInternos(indice);
	for (int i = 0; i < indices.size(); i++)
	{
		double a, p;
		p = perimetro(indices[i]);
		a = area(indices[i]);
		Forma f(p, a);
		cint.push_back(f);
	}
	return cint;
}

// TODO: atualizar conforme mais características forem adicionadas
vector<Forma> ContornosParaDesenho::formas()
{
	if ((*contornos).empty() || (*hierarquia).empty())
	{
		cout << "Contornos ainda nao extraidos ou extraidos de forma nao hierarquica";
	}
	vector<Forma> formas;
	vector<vector<Point>> cont = getContornos();
	vector<vector<Point>> poligonos = poligonosAproximados(0.02, false); // true para visualizar poligonos
	vector<vector<Vec4i>> todosOsDefeitos = defeitosDeConvexidade();
	vector<int> convexos = convexidades();
	vector<double> a, p, circulos = circulosMinimos();
	vector<vector<double>> hu;
	a = areas();
	p = perimetros();
	hu = momentosHu();
	vector<int> indices = indicesDosContornos();
	for (int i = 0; i < cont.size(); i++)
	{
		int x = cont[i][0].x;
		int y = cont[i][0].y;
		vector<Forma> contornosInternos = formasInternas(indices[i]);
		int verticesPoligono = poligonos[i].size(), convexo = convexos[i];
		vector<Vec4i> defeitos = todosOsDefeitos[i];
		vector<double> comprimentoDosDefeitos(defeitos.size());
		for (int j = 0; j < defeitos.size(); j++)
		{
			comprimentoDosDefeitos[j] = defeitos[j][3]/256.0; // índice 3 contem comprimento do defeito em ponto fixo, divisão por 256 converte para ponto flutuante
		}
		double circulo = circulos[i];
		Forma f(p[i], a[i], hu[i], contornosInternos);
		f.setVerticesPoligonoAproximado(verticesPoligono);
		f.setDefeitosDeConvexidade(comprimentoDosDefeitos);
		f.setConvexo(convexo);
		f.setAreaCirculo(circulo);
		f.setX(x);
		f.setY(y);
		formas.push_back(f);
	}
	return formas;
}

vector<Forma> ContornosParaDesenho::formas_r()
{
	vector<Forma> formas;
	vector<cv::Vec4i> defeitos;
	if ((*contornos).empty() || (*contornos).size() == 0 || (*hierarquia).empty())
	{
		cout << "Contornos ainda nao extraidos ou extraidos de forma nao hierarquica";
		return formas;
	}
	vector<vector<Point>> cont = getContornos();
	double a, p, areaCirculo;
	int verticesPoligono, x, y;
	vector<Point> poligono;
	vector<double> hu, circulo;
	vector<Forma> contornosInternos;
	vector<int> indices = indicesDosContornos();
	int retangulo[4][2] = { {0,0}, {0,0}, {0,0}, {0,0} };
	for (int i = 0; i < cont.size(); i++)
	{

		a = area(indices[i]);
		p = perimetro(indices[i]);
		poligono = poligonoAproximado(indices[i]);
		verticesPoligono = poligono.size();

		if (verticesPoligono == 4) 
		{
			retangulo[0][0] = poligono.at(0).x;
			retangulo[0][1] = poligono.at(0).y;
			retangulo[1][0] = poligono.at(1).x;
			retangulo[1][1] = poligono.at(1).y;
			retangulo[2][0] = poligono.at(2).x;
			retangulo[2][1] = poligono.at(2).y;
			retangulo[3][0] = poligono.at(3).x;
			retangulo[3][1] = poligono.at(3).y;
		}
		else 
		{
			float distancias[2] = { 0, 0 };
			int i1=0, j1=0, i2=0, j2=0;
			for (int i = 0; i < verticesPoligono; i++)
			{
				float maiorDistancia = 0;
				int jMaiorDistancia = 0;
				for (int j = 0; j < verticesPoligono; j++)
				{
					if (i != j)
					{
						float distancia = sqrt(pow((double)(poligono.at(i).x - poligono.at(j).x), 2)
							+ pow((double)(poligono.at(i).y - poligono.at(j).y), 2));
						if (distancia >= maiorDistancia)
						{
							maiorDistancia = distancia;
							jMaiorDistancia = j;
						}
					}
				}
				if (distancias[0] <= distancias[1])
				{
					distancias[0] = maiorDistancia;
					i1 = i;
					j1 = jMaiorDistancia;
				}
				else
				{
					distancias[1] = maiorDistancia;
					i2 = i;
					j2 = jMaiorDistancia;
				}
			}
			retangulo[0][0] = poligono.at(i1).x;
			retangulo[0][1] = poligono.at(i1).y;
			retangulo[1][0] = poligono.at(i2).x;
			retangulo[1][1] = poligono.at(i2).y;
			retangulo[2][0] = poligono.at(j1).x;
			retangulo[2][1] = poligono.at(j1).y;
			retangulo[3][0] = poligono.at(j2).x;
			retangulo[3][1] = poligono.at(j2).y;
		}
		
		defeitos = defeitoDeConvexidade(indices[i]);
		vector<double> comprimentoDosDefeitos(defeitos.size());
		for (int j = 0; j < defeitos.size(); j++)
		{
			comprimentoDosDefeitos[j] = defeitos[j][3] / 256.0; // índice 3 contem comprimento do defeito em ponto fixo, divisão por 256 converte para ponto flutuante
		}
		hu = momentoHu(indices[i]);
		circulo = circuloMinimo(indices[i]);
		areaCirculo = circulo[0];
		// TODO: decidir qual posição usar para localizar a forma
		//x = circulo[1]; // define posição como o centro do círculo circunscrito
		//y = circulo[2];
		x = (*contornos)[indices[i]][0].x; // define posição como a posição do primeiro ponto do contorno
		y = (*contornos)[indices[i]][0].y;
		contornosInternos = formasInternas(indices[i]);
		Forma f(p, a, hu, contornosInternos);
		f.setPoligonoAproximado((*contornos)[indices[i]]);
		f.setVerticesPoligonoAproximado(verticesPoligono);
		f.setDefeitosDeConvexidade(comprimentoDosDefeitos);
		f.setAreaCirculo(areaCirculo);
		f.setRetangulo(retangulo);
		f.setX(x);
		f.setY(y);
		formas.push_back(f);
	}
	return formas;
}

ContornosParaDesenho::~ContornosParaDesenho()
{
}
