package implementation;

import interfaces.Ponto;
import interfaces.Retangulo;

public class RetanguloImpl implements Retangulo {
    private Ponto topoEsquerda;
    private Ponto bottomDireita;
    
    public RetanguloImpl(Ponto topoEsquerda, Ponto bottomDireita) {
        this.topoEsquerda = topoEsquerda;
        this.bottomDireita = bottomDireita;
    }
    
    public Ponto getTopoEsquerda() {
        return topoEsquerda;
    }
    
    public Ponto getBottomDireita() {
        return bottomDireita;
    }
    
    @Override
    public String toString() {
    	return "Retangulo (" +
    			getTopoEsquerda() +
    			" " + getBottomDireita() +
    			") ";
    }
}
