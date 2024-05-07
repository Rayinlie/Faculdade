package implementation;

import interfaces.Ponto;
import interfaces.Triangulo;

public class TrianguloImpl implements Triangulo, Cloneable {
    private Ponto vertice1;
    private Ponto vertice2;
    private Ponto vertice3;
    
    public TrianguloImpl(Ponto vertice1, Ponto vertice2, Ponto vertice3) {
        this.vertice1 = vertice1;
        this.vertice2 = vertice2;
        this.vertice3 = vertice3;
    }
    
    public void setVertice1(Ponto vertice1) {
		this.vertice1 = vertice1;
	}

	public void setVertice2(Ponto vertice2) {
		this.vertice2 = vertice2;
	}

	public void setVertice3(Ponto vertice3) {
		this.vertice3 = vertice3;
	}

	public Ponto getVertice1() {
        return vertice1;
    }
    
    public Ponto getVertice2() {
        return vertice2;
    }
    
    public Ponto getVertice3() {
        return vertice3;
    }
    
    @Override
    public Object clone() {
    	try {
    		TrianguloImpl clone = (TrianguloImpl) super.clone();
    		clone.setVertice1((Ponto) this.vertice1.clone());
    		clone.setVertice2((Ponto) this.vertice2.clone());
    		clone.setVertice3((Ponto) this.vertice3.clone());
    		return clone;
    	} catch (CloneNotSupportedException e) {
    		return null;
    	}
    }
    
    @Override
    public String toString() {
    	return "Triangulo (" +
    			getVertice1() +
    			" " + getVertice2() +
    			" " + getVertice3() + 
    			") ";
    }
}