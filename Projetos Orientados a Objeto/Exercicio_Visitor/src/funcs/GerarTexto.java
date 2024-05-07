package funcs;

import docs.Grafico;
import docs.Planilha;
import docs.Texto;
import interfaces.Visitante;

public class GerarTexto implements Visitante {

	@Override
	public Object visitar(Planilha p) {
		p.gerarTexto();
		return null;
	}

	@Override
	public Object visitar(Texto t) {
		t.gerarTexto();
		return null;
	}

	@Override
	public Object visitar(Grafico g) {
		g.gerarPNG();
		return null;
	}

}
