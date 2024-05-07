package concreto;

import interfaces.Estado;

public class Lancando implements Estado{

	@Override
	public void printEmocao() {
		System.out.println("Estou Feliz");
	}
	
}
