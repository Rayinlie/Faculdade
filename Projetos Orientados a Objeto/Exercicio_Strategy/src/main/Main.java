package main;

import concretas.Leilao;

public class Main {
	
	public static void main(String[] args) {

	Leilao leilao = new Leilao(5000);
	
	leilao.definirEstrategia();
	leilao.declararMovimento();
	leilao.encerrarMovimento();
	
	
	}	
}