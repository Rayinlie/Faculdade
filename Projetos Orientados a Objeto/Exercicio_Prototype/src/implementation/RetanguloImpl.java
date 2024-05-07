package implementation;

import interfaces.Ponto;
import interfaces.Retangulo;

public class RetanguloImpl implements Retangulo, Cloneable {
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
    
    public void setTopoEsquerda(Ponto topoEsquerda) {
		this.topoEsquerda = topoEsquerda;
	}

	public void setBottomDireita(Ponto bottomDireita) {
		this.bottomDireita = bottomDireita;
	}

	@Override
    public Object clone() {
    	try {
    		RetanguloImpl clone = (RetanguloImpl) super.clone();
    		clone.setTopoEsquerda((Ponto) this.topoEsquerda.clone());
    		clone.setBottomDireita((Ponto) this.bottomDireita.clone());
    		return clone;
    	} catch (CloneNotSupportedException e) {
    		return null;
    	}
    }
    
    @Override
    public String toString() {
    	return "Retangulo (" +
    			getTopoEsquerda() +
    			" " + getBottomDireita() +
    			") ";
    }
}
