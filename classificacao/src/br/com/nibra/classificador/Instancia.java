package br.com.nibra.classificador;

import weka.core.Attribute;
import weka.core.FastVector;
import weka.core.Instance;
import weka.core.Instances;

/**
 * Classe que representa um dado (conjunto de caracter�sticas) a ser
 * classificado.
 * 
 * @author Thiago
 *
 */
public class Instancia {

	private Instance instance;
	
	/**
	 * Cria uma inst�ncia a partir de uma string com dados.
	 * @param dados Deve ser uma sequ�ncia de descri��es textuais e 
	 * caracter�sticas num�ricas separadas por v�rgula. Exemplo:
	 * "atributo1:1,atributo2:2,atributo3,3.0"
	 */
	public Instancia(String dados) { 
		String[] dadosSeparados = dados.split(",");
		double[] valores = new double[dadosSeparados.length];
		FastVector atributos = new FastVector();
		for(int i = 0; i < dadosSeparados.length; i++) {
			String[] dado = dadosSeparados[i].split(":");
			String descricao = dado[0];
			valores[i] = Double.parseDouble(dado[1]);
			Attribute atributo = new Attribute(descricao, i);
			atributos.addElement(atributo);
		}
		// Criando o atributo que representa as poss�ves classifica��es da inst�ncia
		Attribute classe = atributoClasse();
		atributos.addElement(classe);
		Instances instancias = new Instances("instancias", atributos, 0);
		instancias.setClass(classe);
		Instance inst = new Instance(1.0, valores);
		inst.setDataset(instancias);
		this.instance = inst;
	}

	public Instance getInstance() {
		return instance;
	}

	public void setInstance(Instance instance) {
		this.instance = instance;
	}
	
	/**
	 * Fun��o respons�vel por criar o atributo de {@link Instances} que cont�m
	 * as poss�veis classes dentre as quais uma inst�ncia ser� classificada.
	 * TODO Alterar caso ocorram mudan�as nas poss�veis classifica��es.
	 * @return
	 */
	private Attribute atributoClasse() {
		FastVector classes = new FastVector();
		classes.addElement("fogo");
		classes.addElement("gelo");
		classes.addElement("agua");
		classes.addElement("buraco");
		classes.addElement("muro");
		classes.addElement("nuvem");
		Attribute classe = new Attribute("tipo", classes);
		return classe;
	}

}
