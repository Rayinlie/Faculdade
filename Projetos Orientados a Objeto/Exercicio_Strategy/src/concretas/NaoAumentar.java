package concretas;

import interfaces.Estrategia;

public class NaoAumentar implements Estrategia{

	@Override
	public void movimento() {
		Aguardar();
	}

	@Override
	public void concluir() {
		irParaCasa();
	}
	
	public void Aguardar() {
		System.out.println("Buscando proximo produto");
	}

	public void irParaCasa() {
		System.out.println("Indo para casa triste");
	}
	
	
}
