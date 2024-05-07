package docs;

import interfaces.Documento;
import interfaces.Visitante;

public class Texto implements Documento {
	public Object aceitar(Visitante v) {
		return v.visitar(this);
	}
	
	public void gerarHTML() {
		System.out.println("HTML do Texto gerado!");
	}
	
	public void gerarTexto() {
		System.out.println("Texto gerado!");
	}
	
	public void gerarXML() {
		System.out.println("Gerando XML");
	}
	
	public String toString() {
		return "Texto ";
	}
}