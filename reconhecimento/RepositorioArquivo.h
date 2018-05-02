#pragma once
#include "Repositorio.h"

// Classe que implementa servi�os para manuten��o de dados em arquivos.
class RepositorioArquivo:
	public Repositorio
{
private:
	string nomeArquivo;
	string diretorio; 
public:
	RepositorioArquivo(string nome = "caracteristicas");
	string getNomeArquivo();
	string getDiretorio();
	void setNomeArquivo(string nome);
	void setDiretorio(string dir); 
	void salvar(vector<Forma> formas); // Recebe um conjunto (vetor) de formas e armazena todas as suas caracter�sticas em um arquivo.
	void salvar(vector<string> dados, string cabecalho); // Recebe um vetor de strings contendo informa��es a serem slavas em arquivo.
	~RepositorioArquivo();
};

