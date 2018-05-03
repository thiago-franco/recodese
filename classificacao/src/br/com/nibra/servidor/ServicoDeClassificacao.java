package br.com.nibra.servidor;

import java.io.IOException;

import br.com.nibra.classificador.ClassificacaoDeDesenhos;

public class ServicoDeClassificacao implements Runnable {
	
	private ClassificacaoDeDesenhos classificador;
	private Server servidor;
	public static final int porta = 1505;
	public static final int pacotes = 1;
	public static final char fim = '#';
	
	public ServicoDeClassificacao() throws IOException {
		classificador = new ClassificacaoDeDesenhos();
		servidor = new Server(porta, -1);
		System.out.println("Inicializando...\nClassificacao: ouvindo porta " + porta);
	}
	
	public void executarClassificacao() {
		try {
			while (true) {
				try {
					System.out.println("Classificacao: aguardando conexao...");
					servidor.Connect();

					for (int i = 0; i < pacotes; i++) {
						System.out.println("Classificacao: recebendo pacote de requisicao...");
						String requisicao = servidor.RecvString(fim);
						System.out.println("Classificacao - pacote " + i + ": " + requisicao);

						System.out.println("Classificacao: enviando pacote de resposta...");
						int resposta = classificador.classificar(requisicao);
						resposta = classificador.confirmarClassificacao(requisicao, resposta);
						String resp = Integer.toString(resposta)+'\0';
						servidor.SendString(resp);
						System.out.println("Classificacao - pacote " + i + ": " + resp);
					}

					System.out.println("Classificacao: fechando conexao...");
					servidor.Close();

					System.out.println("Classificacao: encerrado.");

				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}


	@Override
	public void run() {
		executarClassificacao();

	}

}
