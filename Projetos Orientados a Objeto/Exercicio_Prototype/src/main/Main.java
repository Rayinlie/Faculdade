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

		
		Ponto p1 = fabrica.criarPonto(0, 0);
		Ponto p2 = p1.clone();
		System.out.println("P1 = " + p1);
		System.out.println("P2 = " + p2);
		
		Circulo c1 = fabrica.criarCirculo(ponto, 10);
		Circulo c2 = (Circulo) c1.clone();
		System.out.println("C1 = " + c1);
		System.out.println("C2 = " + c2);
		
		Retangulo r1 = fabrica.criarRetangulo(ponto, p1);
		Retangulo r2 = (Retangulo) r1.clone();
		System.out.println("R1 = " + r1);
		System.out.println("R2 = " + r2);
		
		Triangulo t1 = fabrica.criarTriangulo(ponto, p2, fabrica.criarPonto(30, 20));
		Triangulo t2 = (Triangulo) t1.clone();
		System.out.println("T1 = " + t1);
		System.out.println("T2 = " + t2);
		
	}
}
