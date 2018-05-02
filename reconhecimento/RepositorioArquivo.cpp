#include "RepositorioArquivo.h"
#include <fstream>

RepositorioArquivo::RepositorioArquivo(string nome)
{
	setNomeArquivo(nome);
	setDiretorio("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\");
}

string RepositorioArquivo::getNomeArquivo()
{
	return nomeArquivo;
}

string RepositorioArquivo::getDiretorio()
{
	return diretorio;
}

void RepositorioArquivo::setNomeArquivo(string nome)
{
	nomeArquivo = nome;
}

void RepositorioArquivo::setDiretorio(string dir)
{
	diretorio = dir;
}

// TODO: atualizar para cada nova característica adicionada à forma
void RepositorioArquivo::salvar(vector<Forma> dados)
{
	ofstream arquivo(diretorio.append(nomeArquivo).append(".csv"));
	arquivo << (char *)Forma::caracteristicas().c_str() << endl;
	for (int i = 0; i < dados.size(); i++)
	{
		vector<double> momentosHu = dados[i].getMomentosHu();
		arquivo << dados[i].getPerimetro() << ","
			<< dados[i].getArea() << ","
			<< dados[i].qtdContornosInternos() << "," 
			<< momentosHu[0] << "," 
			<< momentosHu[1] << ","
			<< momentosHu[2] << ","
			<< momentosHu[3] << ","
			<< momentosHu[4] << ","
			<< momentosHu[5] << ","
			<< momentosHu[6] << ","
			<< (char *)dados[i].getTipo().c_str() << endl;
	}
}

void RepositorioArquivo::salvar(vector<string> dados, string cabecalho)
{
	ofstream arquivo(diretorio.append(nomeArquivo).append(".csv"));
	arquivo << cabecalho.c_str() << endl;
	for (int i = 0; i < dados.size(); i++)
	{
		arquivo << dados[i].c_str() << endl;
	}
}

RepositorioArquivo::~RepositorioArquivo()
{
}
