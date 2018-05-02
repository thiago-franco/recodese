#include "Imagem.h"
#include "Filtro.h"
#include "Contornos.h"
#include "ContornosParaDesenho.h"
#include "Forma.h"
#include "RepositorioArquivo.h"
#include "ClienteDeClassificacao.h"
#include "TiposDeDesenho.h"
#include "Video.h"
#include "ReconhecimentoDeDesenhos.h"
#include <Windows.h>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
//#include <GLFW/glfw3.h>

// Other includes
#include "Shader.h"
#include "Reconstrucao3DdeDesenhos.h"

using namespace std;

static void testarImagem()
{
	string caminho = "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\nibra\\data\\desenhos.jpg";
	Imagem img(caminho), img2, img3;
	cout << img.getCaminho() << endl;
	img.mostrarImagem();
	caminho = "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\nibra\\data\\baboon.jpg";
	img.carregarImagem(caminho);
	img = img.paraEscalaCinza();
	img.setNome("imagem cinza");
	img.mostrarImagem();
	img2.carregarImagem(caminho);
	img2.mostrarImagem();
	caminho = "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\nibra\\data\\shapes.jpg";
	img3.carregarImagem(caminho);
	img3.mostrarImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
	img2.setImagem(img.paraEscalaCinza().getImagem());
	img2.mostrarImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
}

static void testarFiltro()
{
	Imagem * img = new Imagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\nibra\\data\\baboon.jpg");
	Filtro filtro(img);
	filtro.getImgFiltrada()->mostrarImagem();
	filtro.blur(8);
	filtro.getImgOriginal()->mostrarImagem();
	filtro.getImgFiltrada()->mostrarImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
	img->carregarImagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\nibra\\data\\LinuxLogo.jpg");
	filtro.setImgOriginal(img);
	filtro.getImgOriginal()->mostrarImagem();
	filtro.dilatar(5);
	filtro.getImgFiltrada()->mostrarImagem();
	filtro.erodir(5);
	filtro.getImgFiltrada()->mostrarImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
	// Abrindo imagem...
	filtro.getImgOriginal()->mostrarImagem();
	filtro.manterFiltro();
	filtro.getImgOriginal()->mostrarImagem();
	filtro.dilatar(5);
	filtro.getImgFiltrada()->setNome("Imagem Aberta");
	cout << filtro.getImgFiltrada()->getNome() << endl;
	filtro.getImgFiltrada()->mostrarImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
	img->carregarImagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\nibra\\data\\lena.jpg");
	filtro.setImgOriginal(img);
	filtro.getImgOriginal()->mostrarImagem();
	filtro.blur(10);
	filtro.manterFiltro();
	filtro.edges(150);
	filtro.manterFiltro();
	filtro.erodir(2);
	filtro.getImgFiltrada()->mostrarImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
	filtro.getImgFiltrada()->mostrarImagem();
	filtro.setImgOriginal(img);
	filtro.cannyEdges(80);
	filtro.getImgFiltrada()->mostrarImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
	img->carregarImagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\desenhos\\base-lápis\\base (15).jpg");
	filtro.setImgOriginal(img);
	filtro.segmentar(50);
	filtro.getImgFiltrada()->mostrarImagem();
	Imagem::manterExibicao();
}

static void testarContornos()
{
	Imagem * img = new Imagem();
	img->carregarImagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\nibra\\data\\shapes.jpg");
	Contornos cont(img);
	cont.visualizarContornos();
	cont.extrairArestas(150);
	cont.extrairContornos(false);
	cont.getArestas()->getImgOriginal()->mostrarImagem();
	cont.getArestas()->getImgFiltrada()->mostrarImagem();
	cont.visualizarContornosNaImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
	cont.extrairArestas(150, 2);
	cont.extrairContornos(true);
	cont.getArestas()->getImgOriginal()->mostrarImagem();
	cont.getArestas()->getImgFiltrada()->mostrarImagem();
	Imagem _img = cont.visualizarContornos(1);
	_img.mostrarImagem();
	vector<double> p, a;
	vector<vector<double>> hu;
	p = cont.perimetros();
	a = cont.areas();
	hu = cont.momentosHu();
	Imagem::manterExibicao();	
	Imagem::encerrarExibicao();
}

static void testarContornosParaDesenho()
{
	Imagem * img = new Imagem();
	//img->carregarImagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\nibra\\data\\shapes.jpg", true);
	img->carregarImagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\treino\\agua\\agua (1).jpg", true);
	/*ContornosParaDesenho cont(img);
	cont.extrairArestas(100, 2);
	cont.extrairContornos(false);
	cont.getArestas()->getImgFiltrada()->mostrarImagem();
	cont.visualizarContornos(1);
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
	cont.extrairArestas(100, 1);
	cont.extrairContornos(true);
	cont.getArestas()->getImgFiltrada()->mostrarImagem();
	cont.visualizarContornos(1);
	vector<double> p, a;
	vector<vector<double>> hu;
	p = cont.perimetros();
	a = cont.areas();
	hu = cont.momentosHu();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();*/

	ContornosParaDesenho cont(img);
	cont.extrairArestas(50, 1);
	cont.getArestas()->getImgOriginal()->mostrarImagem();
	cont.getArestas()->getImgFiltrada()->mostrarImagem();
	cont.extrairContornos(true);
	cont.getArestas()->getImgFiltrada()->mostrarImagem();
	cont.visualizarContornosNaImagem();
	Imagem::manterExibicao();
	Imagem::encerrarExibicao();
}

static void testarContornosParaDesenhosEmFotos()
{
	Imagem * img = new Imagem();
	for (int i = 1; i <= 5; i++)
	{
		string caminho = "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\desenhos\\camera\\camera (";
		caminho = caminho + to_string(static_cast<long long>(i)) + ").jpg";
		cout << caminho << endl;
		img->setNome("Base " + to_string(static_cast<long long>(i)));
		img->carregarImagem(caminho, true);
		//img.redimensionar(800, 600);
		ContornosParaDesenho cont(img);
		cont.extrairArestas(50, 1);
		cont.getArestas()->getImgOriginal()->mostrarImagem();
		cont.getArestas()->getImgFiltrada()->mostrarImagem();
		cont.extrairContornos(true);
		cont.getArestas()->getImgFiltrada()->mostrarImagem();
		cont.visualizarContornosNaImagem();
		Imagem::manterExibicao();
		Imagem::encerrarExibicao();
	}
}

static void testarRepositorioArquivos()
{
	vector<Forma> vazio(); 
	double mu[] = { 1, 2, 3, 4, 5, 6, 7 };
	/*Forma d1(5.2, 12.5, mu, vazio, "nuvem");
	Forma d2(7.3, 9.03, mu, {}, "fogo");
	Forma d3(2.15, 4.63, mu, {}, "buraco");
	vector<Forma> d;
	d.push_back(d1);
	d.push_back(d2);
	d.push_back(d3);
	RepositorioArquivo rep;
	rep.salvar(d);*/
}

static void testarExtracaoDeCaracteristicas(vector<cv::Vec4i> defeitos, vector<int> hull)
{
	Imagem * img = new Imagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\\\treino\\muro\\muro (1).jpg", true);
	ContornosParaDesenho cont(img);
	cont.extrairArestas(100);
	cont.extrairContornos();
	vector<Forma> formas = cont.formas_r();
	RepositorioArquivo rep("teste de extracao de caracteristicas");
	rep.salvar(formas);
	/*
	cv::line(img->getImagem(), cv::Point(498, 392), cv::Point(504, 432), cv::Scalar(255, 0, 0));
	cv::line(img->getImagem(), cv::Point(504, 432), cv::Point(585, 433), cv::Scalar(255, 0, 0));
	cv::line(img->getImagem(), cv::Point(585, 433), cv::Point(584, 391), cv::Scalar(255, 0, 0));
	cv::line(img->getImagem(), cv::Point(584, 391), cv::Point(498, 392), cv::Scalar(255, 0, 0));
	*/
	/*cv::line(img->getImagem(), cv::Point(147, 339), cv::Point(159, 434), cv::Scalar(255, 0, 0));
	cv::line(img->getImagem(), cv::Point(159, 434), cv::Point(293, 428), cv::Scalar(255, 0, 0));
	cv::line(img->getImagem(), cv::Point(293, 428), cv::Point(277, 336), cv::Scalar(255, 0, 0));
	cv::line(img->getImagem(), cv::Point(277, 336), cv::Point(147, 339), cv::Scalar(255, 0, 0));*/
	
	img->mostrarImagem();
	Imagem::manterExibicao();
}

static void testarExtracaoDeCaracteristicas2()
{
	//Imagem * img = new Imagem("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\\\treino\\agua\\agua (1).jpg", true);
	Imagem * img = new Imagem("C:\\Users\\Thiago\\Downloads\\IMG_20170214_213449.jpg", true);
	Imagem img2(img->getImagem());
	ContornosParaDesenho cont(img);
	cont.extrairArestas(100);
	cont.extrairContornos();
	vector<Forma> formas = cont.formas_r();
	//RepositorioArquivo rep("teste de extracao de caracteristicas");
	//rep.salvar(formas);
	/*for (int i = 0; i < formas.size(); i++) {
		
		vector<cv::Point> pontos = formas[i].getPoligonoAproximado();
		if (pontos.size() == 583){
		for (int j = 0; j < pontos.size() - 1; j++) {
			cv::line(img->getImagem(), cv::Point(pontos[j].x, pontos[j].y), cv::Point(pontos[j+1].x, pontos[j+1].y), cv::Scalar(0, 0, 255));
		}
		cv::line(img->getImagem(), cv::Point(pontos[pontos.size()-1].x, pontos[pontos.size() - 1].y), cv::Point(pontos[0].x, pontos[0].y), cv::Scalar(0, 0, 255));
		}
	}*/
	cv::line(img2.getImagem(), cv::Point(155, 291), cv::Point(190, 211), cv::Scalar(0, 255, 0));
	cv::line(img2.getImagem(), cv::Point(190, 211), cv::Point(406, 259), cv::Scalar(0, 255, 0));
	cv::line(img2.getImagem(), cv::Point(406, 259), cv::Point(386, 312), cv::Scalar(0, 255, 0));
	cv::line(img2.getImagem(), cv::Point(386, 312), cv::Point(155, 291), cv::Scalar(0, 255, 0));
	//img->mostrarImagem();
	img2.mostrarImagem();
	Imagem::manterExibicao();
}

static void testarExtracaoDeCaracteristicasEmFotos()
{
	ReconhecimentoDeDesenhos recodese;

	recodese.obterDadosDeTreino(2, -1, 100, "teste_muro", "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\treino\\");
	string arquivos[] = { "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\treino\\muro\\muro (1).jpg", "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\treino\\buraco\\buraco (2).jpg", "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\treino\\nuvem\\nuvem (1).jpg", "C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\treino\\nuvem\\nuvem (2).jpg" };
	string tipos[] = { "buraco", "buraco", "nuvem", "nuvem" };
	vector<string> arquivosVec(arquivos, arquivos + 4);
	vector<string> tiposVec(tipos, tipos + 4);
	recodese.obterDadosDeTreino(arquivosVec, tiposVec, "treino_v2_nuvem-buraco", 100);
}

static void testarClienteDeClassificacao()
{
	char *dados0, *dados1, *dados2, *dados3, *dados4, *dados5, *dados6;
	// fogo
	dados0 = "proporcao area perimetro:8.977525,vertices:10,defeitos:14,proporcao defeitos:0.376971,proporcao circulo minimo:0.452961,contornos internos:7,proporcao perimetros internos:0.443686,proporcao areas internas:0.039232,proporcao contornos internos:0.009849,h1:0.174754,h2:0.000872,h3:0.000939,h4:0.000002,h5:0,h6:0,h7:0#";
	dados1 = "proporcao area perimetro:6.918336,vertices:6,defeitos:10,proporcao defeitos:0.408627,proporcao circulo minimo:0.662961,contornos internos:3,proporcao perimetros internos:0.070834,proporcao areas internas:0.00362,proporcao contornos internos:0.007387,h1:0.238748,h2:0.016208,h3:0.007253,h4:0.001143,h5:0.000003,h6:0.000142,h7:0.000001#";
	// gelo
	dados2 = "proporcao area perimetro:2.666908,vertices:14,defeitos:10,proporcao defeitos:0.362608,proporcao circulo minimo:0.822112,contornos internos:2,proporcao perimetros internos:0.025031,proporcao areas internas:0.00423,proporcao contornos internos:0.063363,h1:0.560749,h2:0.184084,h3:0.005468,h4:0.001585,h5:0.000005,h6:0.000356,h7:-0.000001#";
	// agua
	dados3 = "proporcao area perimetro:15.3686,vertices:7,defeitos:29,proporcao defeitos:0.473845,proporcao circulo minimo:0.68142,contornos internos:1,proporcao perimetros internos:0.016406,proporcao areas internas:0.000377,proporcao contornos internos:0.001497,h1:0.296167,h2:0.062063,h3:0,h4:0,h5:0,h6:0,h7:0#";
	// buraco
	dados4 = "proporcao area perimetro:20.731575,vertices:8,defeitos:34,proporcao defeitos:0.408627,proporcao circulo minimo:0.23791,contornos internos:13,proporcao perimetros internos:0.316452,proporcao areas internas:0.007669,proporcao contornos internos:0.001169,h1:0.163808,h2:0.001438,h3:0.00001,h4:0,h5:0,h6:0,h7:0#";
	// muro
	dados5 = "proporcao area perimetro:18.658177,vertices:4,defeitos:10,proporcao defeitos:0.394369,proporcao circulo minimo:0.594967,contornos internos:28,proporcao perimetros internos:3.278505,proporcao areas internas:0.384902,proporcao contornos internos:0.006292,h1:0.264464,h2:0.040921,h3:0.000007,h4:0.000001,h5:0,h6:0,h7:0#";
	// nuvem
	dados6 = "proporcao area perimetro:13.596861,vertices:8,defeitos:18,proporcao defeitos:0.455197,proporcao circulo minimo:0.394445,contornos internos:0,proporcao perimetros internos:0,proporcao areas internas:0,proporcao contornos internos:0,h1:0.182127,h2:0.001438,h3:0.006326,h4:0.000335,h5:0.000013,h6:0,h7:0#";
	ClienteDeClassificacao cliente;
	int resposta = cliente.requisitarClassificacao(dados4, true);
	string tipo = TiposDeDesenho::emString(resposta);
	cout << tipo << endl;
	getchar();
}

static void testarReconhecimentoDeDesenhos()
{
	ReconhecimentoDeDesenhos recodese;
	//recodese.reconhecerDesenhos(2);
	//recodese.reconhecerDesenhos("C:\\Users\\Thiago\\Google Drive\\UERJ\\IC\\desenhos\\teste.jpg");
	recodese.reconhecerDesenhos("C:\\Users\\Thiago\\Downloads\\IMG_20170709_214117 (2).jpg");
}

//static void testarShader()
//{
//	const GLuint WIDTH = 800, HEIGHT = 600;
//	// Init GLFW
//	glfwInit();
//	// Set all the required options for GLFW
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	// Create a GLFWwindow object that we can use for GLFW's functions
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	// Set the required callback functions
//	//glfwSetKeyCallback(window, key_callback);
//
//	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
//	glewExperimental = GL_TRUE;
//	// Initialize GLEW to setup the OpenGL Function pointers
//	glewInit();
//
//	// Define the viewport dimensions
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//
//	// Build and compile our shader program
//	Shader ourShader("default.vs", "default.frag");
//
//
//	// Set up vertex data (and buffer(s)) and attribute pointers
//	GLfloat vertices[] = {
//		// Positions         // Colors
//		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
//		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
//		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top 
//	};
//	GLuint VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	// Color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glBindVertexArray(0); // Unbind VAO
//
//
//						  // Game loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
//		glfwPollEvents();
//
//		// Render
//		// Clear the colorbuffer
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// Draw the triangle
//		ourShader.use();
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		glBindVertexArray(0);
//
//		// Swap the screen buffers
//		glfwSwapBuffers(window);
//	}
//	// Properly de-allocate all resources once they've outlived their purpose
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	// Terminate GLFW, clearing any resources allocated by GLFW.
//	glfwTerminate();
//}

//int main()
//{
//	//testarImagem();
//	//testarFiltro();
//	//testarContornos();
//	//testarContornosParaDesenho();
//	//testarContornosParaDesenhosEmFotos();
//	//testarRepositorioArquivos();
//	//testarExtracaoDeCaracteristicas();
//	//testarExtracaoDeCaracteristicas2();
//	//testarExtracaoDeCaracteristicasEmFotos();
//	//testarClienteDeClassificacao();
//	testarReconhecimentoDeDesenhos();
//	//testarShader();
//	/*Reconstrucao3DdeDesenhos rec;
//	rec.criarObjetoTeste();
//	system("pause");*/
//}