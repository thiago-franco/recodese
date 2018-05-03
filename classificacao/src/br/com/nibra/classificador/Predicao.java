package br.com.nibra.classificador;

/**
 * Classe que representa o resultado da classifica��o de uma {@link Instancia}
 * atrav�s de um {@link Preditor}.
 * 
 * @author Thiago
 *
 */
public class Predicao {

	private String classe;
	private double valor;

	public String getClasse() {
		return classe;
	}

	public void setClasse(String classe) {
		this.classe = classe;
	}

	public double getValor() {
		return valor;
	}

	public void setValor(double valor) {
		this.valor = valor;
	}
	
	public String toString() {
		return "classe " + this.classe + " e valor " + this.valor;
	}

}
