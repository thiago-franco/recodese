package br.com.nibra.classificador;

public class ClassificacaoDeDesenhos {

	public static final String nomeModelo = "tree_v2.model";
	// TODO alterar diretório para o definitivo
	public static final String diretorioModelo = "modelos/";
	private Preditor preditor;

	public ClassificacaoDeDesenhos() {
		this.preditor = new Preditor(diretorioModelo, nomeModelo);
	}

	public int classificar(String requisicao) {
		Instancia inst = new Instancia(requisicao);
		Predicao predicao = preditor.predizer(inst);
		return (int) predicao.getValor();
	}
	
	public static int reclassificar(String requisicao, String modelo) {
		Instancia inst = new Instancia(requisicao);
		Preditor preditorEspecifico = new Preditor(diretorioModelo, modelo);
		Predicao predicaoEspecifica = preditorEspecifico.predizer(inst);
		return (int) predicaoEspecifica.getValor();
	}
	
	// TODO adicionar mais checagens conforme necessidade e criar equivalente a um tipo enumerado para representar os tipos
	public int confirmarClassificacao(String requisicao, int predicaoAtual) {
		int novaPredicao = predicaoAtual;
		if( predicaoAtual == 2 || predicaoAtual == 5) {
			String novoModelo = "logistic_nuvem-agua_v2.model";
			novaPredicao = reclassificar(requisicao, novoModelo);
			switch (novaPredicao) {
			case 0: // TODO criar enumeração para representar os tipos
				novaPredicao = 2; 
				break;
			case 1:
				novaPredicao = 5;
			default:
				break;
			}
		}
		if( predicaoAtual == 3 || predicaoAtual == 5) {
			String novoModelo = "tree_nuvem-buraco.model";
			novaPredicao = reclassificar(requisicao, novoModelo);
			switch (novaPredicao) {
			case 0:
				novaPredicao = 3;
				break;
			case 1:
				novaPredicao = 5;
			default:
				break;
			}
		}
		return novaPredicao;
	}

	public static void main(String[] args) {
		testarClassificacao();
	}

	
	public static void testarClassificacao() {
		String dados1, dados2, dados3, dados4, dados5, dados6;
		// fogo
		dados1 = "proporcao area perimetro:6.918336," + "vertices:6," + "defeitos:10," + "proporcao defeitos:0.408627,"
				+ "proporcao circulo minimo:0.662961," + "contornos internos:3,"
				+ "proporcao perimetros internos:0.070834," + "proporcao areas internas:0.00362,"
				+ "proporcao contornos internos:0.007387," + "h1:0.238748," + "h2:0.016208," + "h3:0.007253,"
				+ "h4:0.001143," + "h5:0.000003," + "h6:0.000142," + "h7:0.000001";
		// gelo
		dados2 = "proporcao area perimetro:2.666908," + "vertices:14," + "defeitos:10," + "proporcao defeitos:0.362608,"
				+ "proporcao circulo minimo:0.822112," + "contornos internos:2,"
				+ "proporcao perimetros internos:0.025031," + "proporcao areas internas:0.00423,"
				+ "proporcao contornos internos:0.063363," + "h1:0.560749," + "h2:0.184084," + "h3:0.005468,"
				+ "h4:0.001585," + "h5:0.000005," + "h6:0.000356," + "h7:-0.000001";
		// agua
		dados3 = "proporcao area perimetro:15.3686," + "vertices:7," + "defeitos:29," + "proporcao defeitos:0.473845,"
				+ "proporcao circulo minimo:0.68142," + "contornos internos:1,"
				+ "proporcao perimetros internos:0.016406," + "proporcao areas internas:0.000377,"
				+ "proporcao contornos internos:0.001497," + "h1:0.296167," + "h2:0.062063," + "h3:0," + "h4:0,"
				+ "h5:0," + "h6:0," + "h7:0";
		// buraco
		dados4 = "proporcao area perimetro:20.731575," + "vertices:8," + "defeitos:34," + "proporcao defeitos:0.408627,"
				+ "proporcao circulo minimo:0.23791," + "contornos internos:13,"
				+ "proporcao perimetros internos:0.316452," + "proporcao areas internas:0.007669,"
				+ "proporcao contornos internos:0.001169," + "h1:0.163808," + "h2:0.001438," + "h3:0.00001," + "h4:0,"
				+ "h5:0," + "h6:0," + "h7:0";
		// muro
		dados5 = "proporcao area perimetro:18.658177," + "vertices:4," + "defeitos:10," + "proporcao defeitos:0.394369,"
				+ "proporcao circulo minimo:0.594967," + "contornos internos:28,"
				+ "proporcao perimetros internos:3.278505," + "proporcao areas internas:0.384902,"
				+ "proporcao contornos internos:0.006292," + "h1:0.264464," + "h2:0.040921," + "h3:0.000007,"
				+ "h4:0.000001," + "h5:0," + "h6:0," + "h7:0";
		// nuvem
		dados6 = "proporcao area perimetro:13.596861," + "vertices:8," + "defeitos:18," + "proporcao defeitos:0.455197,"
				+ "proporcao circulo minimo:0.394445," + "contornos internos:0," + "proporcao perimetros internos:0,"
				+ "proporcao areas internas:0," + "proporcao contornos internos:0," + "h1:0.182127," + "h2:0.001438,"
				+ "h3:0.006326," + "h4:0.000335," + "h5:0.000013," + "h6:0," + "h7:0";
		Instancia inst = new Instancia(dados1);
		try {
			Preditor preditor = new Preditor(diretorioModelo, nomeModelo);
			Predicao resultado = preditor.predizer(inst);
			System.out.println(resultado.toString());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}