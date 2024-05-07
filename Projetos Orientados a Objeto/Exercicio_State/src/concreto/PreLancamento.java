package concreto;

import interfaces.Estado;

public class PreLancamento implements Estado {

	@Override
	public void printEmocao() {
		System.out.println("Estou interessado");
	}

}
