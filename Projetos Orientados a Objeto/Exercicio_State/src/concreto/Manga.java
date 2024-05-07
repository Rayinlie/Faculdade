package concreto;

import interfaces.Estado;

public class Manga {
	
	public final Estado HIATO = new Hiato();
	public final Estado LANCANDO= new Lancando();
	public final Estado PRE = new PreLancamento();
	public final Estado NULLOBJ = new nullObj();
	
	private Estado estado;
	
	public void setEstado(Estado estado) {
		this.estado = estado;
	}
	
	public void printEmocao() {
		estado.printEmocao();
	}
}
