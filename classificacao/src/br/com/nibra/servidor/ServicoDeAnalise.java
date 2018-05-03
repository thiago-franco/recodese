package br.com.nibra.servidor;

import java.io.IOException;

public class ServicoDeAnalise implements Runnable {
	
	private Server servidor;
	public static final int porta = 1995;
	public static final int pacotes = 1;
	public static final char fim = '\0';
	
	public ServicoDeAnalise() throws IOException {
		servidor = new Server(porta, -1);
	}
	
	public void executarAnalise() {
		try {
			System.out.println("Inicializando...\nAnalise: ouvindo porta " + porta);
			while (true) {
				try {
					System.out.println("Analise: aguardando conexao...");
					servidor.Connect();

					for (int i = 0; i < pacotes; i++) {
						System.out.println("Analise: recebendo pacote de requisicao...");
						String requisicao = servidor.RecvString(fim);
						System.out.println("Analise - pacote " + i + ": " + requisicao);

					}

					System.out.println("Analise: fechando conexao...");
					servidor.Close();

					System.out.println("Analise: encerrado.");

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
		executarAnalise();
	}

}
