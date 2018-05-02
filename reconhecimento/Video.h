#pragma once
#include "Imagem.h"
#include "Forma.h"
//#include <thread>
#include <boost/thread.hpp>

class Video
{
private:
	cv::VideoCapture * captura;
	cv::Mat frame;
	char fimDeVideo;
public:
	Video(int dispositivo = 2);
	char getFimDeVideo();
	void setFimDeVideo(char fdv);
	void frameAtual(Imagem * img); // Adiciona o frame atual da captura à imagem recebida por parâmetro.
	//void executarVideo(Imagem * img, function<void()> callback = NULL); // Executa vídeo.
	void executarVideoExibindoClassificacao(Imagem * img, vector<Forma> * formas); // Executa vídeo.
	// TODO: fazer implementação com callback que funcione
	//boost::thread executarVideoEmThread(Imagem * img, function<void()> callback = NULL); // Executa vídeo em thread individual.
	boost::thread * executarVideoEmThread(Imagem * img, vector<Forma> * formas); // Executa video e exibe classificação das formas.
	bool finalizarCaptura(); // Checa se condições para o término da captura de vídeo foram atingidas.
	~Video();
};

