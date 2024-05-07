package concretas;

import interfaces.Estrategia;

public class Rapido implements Estrategia{
	
	@Override
	public void movimento() {
		aumetoLentoAposta();
	}

	@Override
	public void concluir() {
		avaliarConquistas();
	}
	
	public void aumetoLentoAposta() {
		System.out.println("Aumentar 1000 dólares");
	}
	
	public void avaliarConquistas() {
		System.out.println("Curtindo o lucro");
	}
}
