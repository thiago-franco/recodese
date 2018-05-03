package br.com.nibra.classificador;

import weka.classifiers.Classifier;

/**
 * Classe que permite a classificação de dados a partir de um modelo previamente
 * desenvolvido.
 * 
 * @author Thiago
 * 
 */
public class Preditor {

	private Classifier modelo;

	public Preditor(String diretorioModelo, String nomeModelo) {
		try {
			this.modelo = (Classifier) weka.core.SerializationHelper.read(diretorioModelo + nomeModelo);
		} catch (Exception e) {		
			e.printStackTrace();
		}
	}

	public Classifier getModelo() {
		return modelo;
	}

	public void setModelo(Classifier modelo) {
		this.modelo = modelo;
	}

	public Predicao predizer(Instancia inst) {
		Predicao resultado = new Predicao();
		try {
			double valor = this.modelo.classifyInstance(inst.getInstance());
			String classe = inst.getInstance().classAttribute().value((int) (valor));
			resultado.setValor(valor);
			resultado.setClasse(classe);
		}
		catch(Exception e) {
			e.printStackTrace();
			System.out.println(e.getMessage());
		}
		return resultado;
	}

}
