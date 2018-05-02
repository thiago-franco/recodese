#pragma once

#include "ClienteDeClassificacao.h"
#include "RepositorioArquivo.h"
#include "Forma.h"
#include "Imagem.h"

class ReconhecimentoDeDesenhos
{
private:
	ClienteDeClassificacao * classificador;
	RepositorioArquivo * repositorio;
public:
	  ReconhecimentoDeDesenhos();
	// Obtém dados de treino a partir de fotos contidas no diretório especificado.
	  void obterDadosDeTreino(int qtd, int imagem = -1, int intensidade = 100, string nomeDestino = "dados de treino", string caminho = "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\desenhos\\");
	  void obterDadosDeTreino(vector<string> nomeArquivos, vector<string> tipos, string nomeDestino = "dados de treino",  int intensidade = 100);
	// Executa rotina de classificação de desenhos obtidos através de imagem oriunda do dispositivo especificado.
	  void reconhecerDesenhos(int dispositivo);
	  void reconhecerDesenhos(string caminhoImagem);
	  void reconhecerDesenhos(Imagem * img);
	  vector<Forma> obterFormasReconhecidas(string caminhoImagem);
	// Permite visualizar contornos das formass e seus respectivos tipos associados.
	  static Imagem visualizarClassificacao(vector<Forma> * formas, Imagem contornos, bool exibir = true);
	  ~ReconhecimentoDeDesenhos();
};

