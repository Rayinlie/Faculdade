package main;

import implementation.FabricaDeFormasImpl;
import interfaces.Circulo;
import interfaces.FabricaDeFormas;
import interfaces.Ponto;
import interfaces.Retangulo;
import interfaces.Triangulo;

public class Main {

	public static void main(String[] args) {

		// Exemplo de uso
		FabricaDeFormas fabrica = new FabricaDeFormasImpl();

		Ponto ponto = fabrica.criarPonto(10, 20);
		Circulo circulo = fabrica.criarCirculo(ponto, 5);
		Retangulo retangulo = fabrica.criarRetangulo(ponto, fabrica.criarPonto(30, 40));
		Triangulo triangulo = fabrica.criarTriangulo(ponto, fabrica.criarPonto(30, 20), fabrica.criarPonto(20, 30));
		
		
		System.out.println(ponto);
		System.out.println(circulo);
		System.out.println(retangulo);
		System.out.println(triangulo);
	}

}
