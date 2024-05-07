package docs;

import interfaces.Documento;
import interfaces.Visitante;

public class Planilha implements Documento {
	
	public Object aceitar(Visitante v) {
		return v.visitar(this);
	}
	
	public void gerarHTML() {
		System.out.println("HTML da Planilha gerada!");
	}
	
	public void gerarTexto() {
		System.out.println("Texto da Planilha gerada!");
	}
	
	public void gerarXML() {
		System.out.println("Gerando XML");
	}
	
	public String toString() {
		return "Planilha ";
	}
}
