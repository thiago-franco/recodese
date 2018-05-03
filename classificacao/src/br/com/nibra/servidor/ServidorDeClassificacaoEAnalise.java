package br.com.nibra.servidor;

import java.io.IOException;

public class ServidorDeClassificacaoEAnalise {

	public static void main(String[] args) {
		try {

			ServicoDeClassificacao classificacao = new ServicoDeClassificacao();
			Thread threadClassificacao = new Thread(classificacao);
			threadClassificacao.start();

			ServicoDeAnalise analise = new ServicoDeAnalise();
			Thread threadAnalise = new Thread(analise);
			threadAnalise.start();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
