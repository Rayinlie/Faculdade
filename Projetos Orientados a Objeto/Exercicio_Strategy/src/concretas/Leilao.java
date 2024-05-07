package concretas;

import interfaces.Estrategia;

public class Leilao{
	
	private Estrategia acao;
	private Integer preco;
	
	public Leilao(Integer preco) {
		this.preco = preco;
	}
	public void definirEstrategia() {
		if (preco > 5000) {
			acao = new Lento();
		} else if (preco < 1000) {
			acao = new Rapido();
		} else if (preco >= 10000) {
			acao = new NaoAumentar();
		} else {
			acao = new nullObj();
		}
	}
	public void declararMovimento() {
		acao.movimento();
	}
	public void encerrarMovimento() {
		acao.concluir();
	}
}