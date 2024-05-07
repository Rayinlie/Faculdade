package funcs;

import docs.Grafico;
import docs.Planilha;
import docs.Texto;
import interfaces.Visitante;

public class GerarXML implements Visitante{

	@Override
	public Object visitar(Planilha p) {
		p.gerarXML();
		return null;
	}

	@Override
	public Object visitar(Texto t) {
		t.gerarXML();
		return null;
	}

	@Override
	public Object visitar(Grafico g) {
		g.gerarXML();
		return null;
	}

}
