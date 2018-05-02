#pragma once
#include "Repositorio.h"

// Classe que implementa serviços para manutenção de dados em arquivos.
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
	void salvar(vector<Forma> formas); // Recebe um conjunto (vetor) de formas e armazena todas as suas características em um arquivo.
	void salvar(vector<string> dados, string cabecalho); // Recebe um vetor de strings contendo informações a serem slavas em arquivo.
	~RepositorioArquivo();
};

