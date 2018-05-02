#include "Video.h"
#include "ReconhecimentoDeDesenhos.h"

using namespace std;
using namespace cv;

Video::Video(int dispositivo)
{
	captura = new VideoCapture(dispositivo);
	fimDeVideo = 'q';
}

char Video::getFimDeVideo()
{
	return fimDeVideo;
}

void Video::setFimDeVideo(char fdv)
{
	fimDeVideo = fdv;
}

void Video::frameAtual(Imagem * img)
{
	if (!captura->isOpened())
	{
		cout << "Capture could not be oppend.";
		return;
	}
	*captura >> frame;
	img->setImagem(frame);
}

/*void Video::executarVideo(Imagem * img, function<void()> callback)
{
	while (!finalizarCaptura())
	{
		frameAtual(img);
		img->mostrarImagem();
		if( callback != NULL)
			callback();
	}
}*/

void Video::executarVideoExibindoClassificacao(Imagem * img, vector<Forma> * formas)
{
	while (!finalizarCaptura())
	{
		frameAtual(img);
		img->setImagem(ReconhecimentoDeDesenhos::visualizarClassificacao(formas, *img, false).getImagem());
		img->mostrarImagem();
	}
}

/*thread Video::executarVideoEmThread(Imagem * img, function<void()> callback)
{
	thread videoEmThread(&Video::executarVideo, this, img, callback);
	return videoEmThread;
}*/

boost::thread * Video::executarVideoEmThread(Imagem * img, vector<Forma> * formas)
{
	boost::thread * videoEmThread = new boost::thread(&Video::executarVideoExibindoClassificacao, this, img, formas);
	return videoEmThread;
}

bool Video::finalizarCaptura()
{
	bool finalizar = waitKey(1) == fimDeVideo;
	return finalizar;
}

Video::~Video()
{
	frame.release();
	delete(captura);
}
