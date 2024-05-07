package concretas;

import interfaces.Estrategia;

public class Lento implements Estrategia {

	@Override
	public void movimento() {
		aumetoLentoAposta();
	}

	@Override
	public void concluir() {
		avaliarConquistas();
	}
	
	public void aumetoLentoAposta() {
		System.out.println("Aumentar 200 dólares");
	}
	
	public void avaliarConquistas() {
		System.out.println("Avaliando lucro");
	}
}
