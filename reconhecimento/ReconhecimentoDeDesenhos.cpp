
#include "ReconhecimentoDeDesenhos.h"
#include "TiposDeDesenho.h"
#include "ContornosParaDesenho.h"
#include "Video.h"
#include <ctime>

ReconhecimentoDeDesenhos::ReconhecimentoDeDesenhos()
{
	repositorio = new RepositorioArquivo();
	classificador = new ClienteDeClassificacao();
}

void ReconhecimentoDeDesenhos::obterDadosDeTreino(int qtd, int imagem, int intensidade, string nomeDestino, string caminho)
{
	vector<Forma> dados;
	int indiceImagem = imagem;
	for (int i = 0; i < TiposDeDesenho::quantidadeDeTipos(); i++)
	{
		string diretorio = caminho + TiposDeDesenho::emString(i) + "\\";
		for (int j = 1; j <= qtd; j++)
		{
			indiceImagem = imagem == -1 ? j : imagem;
			string nomeImg = TiposDeDesenho::emString(i) + " (" + to_string(static_cast<long long>(indiceImagem)) + ").jpg";
			transform(nomeImg.begin(), nomeImg.end(), nomeImg.begin(), tolower); // Nome dos tipos estão em maiúsculo mas espera-se nome de arquivo em minúsculo.
			Imagem * imgTreino = new Imagem(diretorio + nomeImg, true);
			ContornosParaDesenho * cont = new ContornosParaDesenho(imgTreino);
			cont->extrairArestas(intensidade);
			cont->extrairContornos();
			cont->visualizarContornosNaImagem();
			Imagem::manterExibicao();
			Imagem::encerrarExibicao();
			delete(imgTreino);
			vector<Forma> desenhos = cont->formas();
			Forma::rotularFormas(&desenhos, TiposDeDesenho::emString(i));
			dados.insert(dados.end(), desenhos.begin(), desenhos.end());
		}
	}
	vector<string> dadosEmTexto(dados.size());
	string cabecalho = Forma::caracteristicas();
	for (int i = 0; i < dados.size(); i++)
	{
		dadosEmTexto[i] = dados[i].caracteristicasEmTexto();
	}
	repositorio->setNomeArquivo(nomeDestino);
	repositorio->salvar(dadosEmTexto, cabecalho);
}

void ReconhecimentoDeDesenhos::obterDadosDeTreino(vector<string> nomeArquivos, vector<string> tipos, string nomeDestino, int intensidade)
{
	vector<Forma> dados;
	for (int i = 0; i < nomeArquivos.size(); i++)
	{
		Imagem * imgTreino = new Imagem(nomeArquivos.at(i), true);
		ContornosParaDesenho * cont = new ContornosParaDesenho(imgTreino);
		cont->extrairArestas(intensidade);
		cont->extrairContornos();
		cont->visualizarContornosNaImagem();
		Imagem::manterExibicao();
		Imagem::encerrarExibicao();
		delete(imgTreino);
		vector<Forma> desenhos = cont->formas();
		Forma::rotularFormas(&desenhos, tipos[i]);
		dados.insert(dados.end(), desenhos.begin(), desenhos.end());
	}
	vector<string> dadosEmTexto(dados.size());
	string cabecalho = Forma::caracteristicas();
	for (int i = 0; i < dados.size(); i++)
	{
		dadosEmTexto[i] = dados[i].caracteristicasEmTexto();
	}
	repositorio->setNomeArquivo(nomeDestino);
	repositorio->salvar(dadosEmTexto, cabecalho);
}

void ReconhecimentoDeDesenhos::reconhecerDesenhos(int dispositivo)
{
	Video * video = new Video(dispositivo);
	Imagem * original = new Imagem();
	original->setNome("Thread de Video");
	vector<Forma> * formasAtuais = new vector<Forma>();
	Imagem * contornosAtuais = new Imagem();
	boost::thread * videoThread = video->executarVideoEmThread(original, formasAtuais);
		//[&original, formasAtuais, contornosAtuais] {original->setImagem(visualizarClassificacao(formasAtuais, *contornosAtuais, false).getImagem());});
	ClienteDeClassificacao classificador;
	while (!video->finalizarCaptura()) {
		Imagem * desenhos = new Imagem();
		video->frameAtual(desenhos);
		ContornosParaDesenho * cont = new ContornosParaDesenho(desenhos);
		cont->extrairArestas(100);
		cont->extrairContornos();
		//clock_t b = clock();
		vector<Forma> formas = cont->formas_r();
		//clock_t e = clock();
		//cout << double(e - b) / CLOCKS_PER_SEC << endl;
		int tipo = -1;
		//cout << "size: " << formas.size() << endl;
		for (int i = 0; i < formas.size(); i++)
		{
			cout << "Classificacao da forma " << i << ":" << endl;
			tipo = classificador.requisitarClassificacao(&formas[i]);
			string tipoEmTexto = TiposDeDesenho::emString(tipo);
			cout << tipo << ": " << tipoEmTexto << endl;	
		}
		*contornosAtuais = cont->visualizarContornosNaImagem(0, false);
		*formasAtuais = formas;
		desenhos->setImagem(visualizarClassificacao(&formas, cont->visualizarContornosNaImagem(0, false), false).getImagem());
		desenhos->setNome("Thread de Processamento");
		desenhos->mostrarImagem();
		delete(cont);
	}
	videoThread->join();
}

void ReconhecimentoDeDesenhos::reconhecerDesenhos(string caminhoImagem)
{
	ClienteDeClassificacao classificador;
	Imagem * desenhos = new Imagem(caminhoImagem, true);
	ContornosParaDesenho * cont = new ContornosParaDesenho(desenhos);
	cont->extrairArestas(100);
	cont->extrairContornos();
	vector<Forma> formas = cont->formas_r();
	int tipo = -1;
	for (int i = 0; i < formas.size(); i++)
	{
		cout << "Classificacao da forma " << i << ":" << endl;
		tipo = classificador.requisitarClassificacao(&formas[i]);
		string tipoEmTexto = TiposDeDesenho::emString(tipo);
		cout << tipo << ": " << tipoEmTexto << endl;
	}
	*desenhos = visualizarClassificacao(&formas, cont->visualizarContornosNaImagem(0, false), false);
	desenhos->mostrarImagem();
	Imagem::manterExibicao();
	delete cont->getArestas();
	free(cont);
}

void ReconhecimentoDeDesenhos::reconhecerDesenhos(Imagem * desenhos)
{
	ClienteDeClassificacao classificador;
	ContornosParaDesenho * cont = new ContornosParaDesenho(desenhos);
	cont->extrairArestas(100);
	cont->extrairContornos();
	vector<Forma> formas = cont->formas_r();
	int tipo = -1;
	for (int i = 0; i < formas.size(); i++)
	{
		tipo = -1;
		cout << "Classificacao da forma " << i << ":" << endl;
		tipo = classificador.requisitarClassificacao(&formas[i]);
		string tipoEmTexto = TiposDeDesenho::emString(tipo);
		cout << tipo << ": " << tipoEmTexto << endl;
	}
	*desenhos = visualizarClassificacao(&formas, cont->visualizarContornosNaImagem(0, false), false);
	desenhos->mostrarImagem();
	Imagem::manterExibicao();
	delete(cont);
}

vector<Forma> ReconhecimentoDeDesenhos::obterFormasReconhecidas(string caminhoImagem)
{
	ClienteDeClassificacao classificador;
	Imagem * desenhos = new Imagem(caminhoImagem, true);
	ContornosParaDesenho * cont = new ContornosParaDesenho(desenhos);
	cont->extrairArestas(100);
	cont->extrairContornos();
	vector<Forma> formas = cont->formas_r();
	int tipo = -1;
	for (int i = 0; i < formas.size(); i++)
	{
		cout << "Classificacao da forma " << i << ":" << endl;
		tipo = classificador.requisitarClassificacao(&formas[i]);
		string tipoEmTexto = TiposDeDesenho::emString(tipo);
		cout << tipo << ": " << tipoEmTexto << endl;
	}
	delete cont->getArestas();
	free(cont);
	return formas;
}

  Imagem ReconhecimentoDeDesenhos::visualizarClassificacao(vector<Forma> * formas, Imagem contornos, bool exibir)
{
	cv::Mat contornosClassificados(contornos.getImagem());
	for (int i = 0; i < formas->size(); i++)
	{
		// TODO: cirar função em Imagem para adicionar texto às imagens e substituir essa chamada direta ao opencv
		cv::putText(contornosClassificados, formas->at(i).getTipo(), cv::Point(formas->at(i).getX(), formas->at(i).getY()), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255));
	}
	Imagem img(contornosClassificados);
	img.setNome("Formas Classificadas");
	if (exibir)
	{
		img.mostrarImagem();
		Imagem::manterExibicao();
	}
	return img;
}

  ReconhecimentoDeDesenhos::~ReconhecimentoDeDesenhos()
{
	delete(repositorio);
	delete(classificador);
}
