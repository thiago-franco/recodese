#include "ClienteDeClassificacao.h"
#include "Client.h"
#include "TiposDeDesenho.h"
#include <iostream>
#include <string>

using namespace std;

ClienteDeClassificacao::ClienteDeClassificacao()
{
	host = "localhost";
	porta = 1505;
	pacotes = 1;
	fim = '#';
}

string ClienteDeClassificacao::getHost()
{
	return host;
}

int ClienteDeClassificacao::getPorta()
{
	return porta;
}

int ClienteDeClassificacao::getPacotes()
{
	return pacotes;
}

char ClienteDeClassificacao::getFim()
{
	return fim;
}

int ClienteDeClassificacao::requisitarClassificacao(Forma * forma, bool debug)
{
	bool sucesso;
	Client cliente((char *)host.c_str(), porta, &sucesso);
	if (sucesso)
	{
		if(debug)
			cout << "Cliente: conexao estabelecida..." << endl << "Cliente: conectado ao servidor em " << host << " na porta " << porta << "..." << endl;
	}
	else
	{
		if (debug)
			cout << "Nao foi possivel estabelecer conexao com servidor." << endl;
	}
	// Obtém dados da requisição a partir da forma e adiciona caracter que 
	// representa fim de linha no protocolo de comunicação com servidor.
	string dados = forma->caracteristicasEmTextoFormatado();
	dados += fim;	
	char * requisicao = (char *)dados.c_str();
	char resposta[1024];
	for (int i = 0; i < pacotes; i++)
	{
		if (debug)
			cout << "Cliente: enviando pacote de requisicao..." << endl;
		cliente.SendString(requisicao);
		if (debug)
			cout << "pacote " << i << ": " << requisicao << endl;

		if (debug)
			cout << "Cliente: recebendo pacote de resposta..." << endl;
		cliente.RecvString(resposta, 1024, fim);
		if (debug)
			cout << "pacote " << i << ": " << resposta << endl;
	}
	if (debug)
		cout << "Cliente: fechando conexao..." << endl;
	cliente.Close();
	if (debug)
		cout << "Cliente: encerrado." << endl;
	int respostaEmInteiro = atoi(resposta);
	forma->setTipo(TiposDeDesenho::emString(respostaEmInteiro));
	return respostaEmInteiro;
}

int ClienteDeClassificacao::requisitarClassificacao(string requisicao, bool debug)
{
	bool sucesso;
	Client cliente((char *)host.c_str(), porta, &sucesso);
	if (sucesso)
	{
		if (debug)
			cout << "Cliente: conexao estabelecida..." << endl << "Cliente: conectado ao servidor em " << host << " na porta " << porta << "..." << endl;
	}
	else
	{
		if (debug)
			cout << "Nao foi possivel estabelecer conexao com servidor." << endl;
	}
	char resposta[1024];
	for (int i = 0; i < pacotes; i++)
	{
		if (debug)
			cout << "Cliente: enviando pacote de requisicao..." << endl;
		cliente.SendString((char *)requisicao.c_str());
		if (debug)
			cout << "pacote " << i << ": " << requisicao << endl;

		if (debug)
			cout << "Cliente: recebendo pacote de resposta..." << endl;
		cliente.RecvString(resposta, 1024, fim);
		if (debug)
			cout << "pacote " << i << ": " << resposta <<endl;
	}
	if (debug)
		cout << "Cliente: fechando conexao..." << endl;
	cliente.Close();
	if (debug)
		cout << "Cliente: encerrado." << endl;
	int respostaEmInteiro = atoi(resposta);
	return respostaEmInteiro;
}

ClienteDeClassificacao::~ClienteDeClassificacao()
{
}
