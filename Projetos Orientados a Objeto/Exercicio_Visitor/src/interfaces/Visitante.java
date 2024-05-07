package interfaces;

import docs.Grafico;
import docs.Planilha;
import docs.Texto;

public interface Visitante {
	
	public Object visitar(Planilha p);
	
	public Object visitar(Texto t);
	
	public Object visitar(Grafico g);
}
