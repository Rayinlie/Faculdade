package funcs;

import docs.Grafico;
import docs.Planilha;
import docs.Texto;
import interfaces.Visitante;

public class Validar implements Visitante {
	public Object visitar(Planilha p) {
		return new Boolean(true); 
	}
	
	public Object visitar(Texto t) {
		return new Boolean(true); 
	}
	
	public Object visitar(Grafico g) {
		return new Boolean(true); 
	}
}