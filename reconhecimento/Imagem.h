#pragma once
#include <opencv2\opencv.hpp>
#include <string>

using namespace std;

//Classe que encapsula funcionalidades b�sicas de manipula��o de imagem da biblioteca OpenCV.
class Imagem
{
private:
	cv::Mat img; // Estrutura de dados fornecida pelo OpenCV para armazenar imagem.
	string caminho; // Caminho para diret�rio de localiza��o da imagem.
	string nome; // Nome para identificar imagem.
public:
	Imagem();
	Imagem(string caminho, bool vga = false); // Cria imagem com resolu��o de 640x480 caso vga = true.
	Imagem(cv::Mat imagem); 
	string getCaminho();
	cv::Mat getImagem();
	string getNome();
	void setCamihno(string c);
	void setNome(string n);
	void setImagem(cv::Mat i);
	bool checarImagem(); // Verifica se o atributo "img" contem uma imagem v�lida.
	void carregarImagem(string caminho, bool vga = false); // Carrega imgagem do caminho recebido no atributo img.
	void redimensionar(int x, int y); // Redimensiona imagem de acordo com par�metros informados.
	Imagem paraEscalaCinza(); // Retorna imagem orgiginal (RGB) convertida para escala de cinza.
	void mostrarImagem(); // Exibe janela com a imagem.
	static void manterExibicao(); // Mantem a exibicao de todas as janelas com imagens at� que uma tecla seja pressionada.
	static void encerrarExibicao(); // Fecha todas as janelas.
	static void cirarJanela(string nome); // Cria janela deexibi��o de imagens.
	~Imagem();
};
