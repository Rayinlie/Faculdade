package concreto;

import interfaces.Estado;

public class Hiato implements Estado {

	@Override
	public void printEmocao() {
		System.out.println("Estou triste");
	}
	
}
