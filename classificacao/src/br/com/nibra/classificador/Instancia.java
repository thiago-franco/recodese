package br.com.nibra.classificador;

import weka.core.Attribute;
import weka.core.FastVector;
import weka.core.Instance;
import weka.core.Instances;

/**
 * Classe que representa um dado (conjunto de características) a ser
 * classificado.
 * 
 * @author Thiago
 *
 */
public class Instancia {

	private Instance instance;
	
	/**
	 * Cria uma instância a partir de uma string com dados.
	 * @param dados Deve ser uma sequência de descrições textuais e 
	 * características numéricas separadas por vírgula. Exemplo:
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
		// Criando o atributo que representa as possíves classificações da instância
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
	 * Função responsável por criar o atributo de {@link Instances} que contém
	 * as possíveis classes dentre as quais uma instância será classificada.
	 * TODO Alterar caso ocorram mudanças nas possíveis classificações.
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
