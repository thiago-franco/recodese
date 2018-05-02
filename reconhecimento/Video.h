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
	void frameAtual(Imagem * img); // Adiciona o frame atual da captura � imagem recebida por par�metro.
	//void executarVideo(Imagem * img, function<void()> callback = NULL); // Executa v�deo.
	void executarVideoExibindoClassificacao(Imagem * img, vector<Forma> * formas); // Executa v�deo.
	// TODO: fazer implementa��o com callback que funcione
	//boost::thread executarVideoEmThread(Imagem * img, function<void()> callback = NULL); // Executa v�deo em thread individual.
	boost::thread * executarVideoEmThread(Imagem * img, vector<Forma> * formas); // Executa video e exibe classifica��o das formas.
	bool finalizarCaptura(); // Checa se condi��es para o t�rmino da captura de v�deo foram atingidas.
	~Video();
};

