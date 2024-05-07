package docs;

import interfaces.Documento;
import interfaces.Visitante;

public class Grafico implements Documento {
	
	public Object aceitar(Visitante v) {
		return v.visitar(this);
	}
	
	public void gerarPNG() {
		System.out.println("PNG Gerado!");
	}
	
	public void gerarXML() {
		System.out.println("Gerando XML");
	}
	
	public String toString() {
		return "Grafico ";
	}
}