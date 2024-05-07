package implementation;

import interfaces.Ponto;
import interfaces.Triangulo;

public class TrianguloImpl implements Triangulo {
    private Ponto vertice1;
    private Ponto vertice2;
    private Ponto vertice3;
    
    public TrianguloImpl(Ponto vertice1, Ponto vertice2, Ponto vertice3) {
        this.vertice1 = vertice1;
        this.vertice2 = vertice2;
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
    public String toString() {
    	return "Triangulo (" +
    			getVertice1() +
    			" " + getVertice2() +
    			" " + getVertice3() + 
    			") ";
    }
}