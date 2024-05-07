package implementation;

import interfaces.Circulo;
import interfaces.Ponto;

public class CirculoImpl implements Circulo, Cloneable {
  
	private Ponto centro;
    private int raio;
    
    public CirculoImpl(Ponto centro, int raio) {
        this.centro = centro;
        this.raio = raio;
    }
    
    public Ponto getCentro() {
        return centro;
    }
    
    public int getRaio() {
        return raio;
    }
    
    public void setCentro(Ponto centro) {
		this.centro = centro;
	}

	public void setRaio(int raio) {
		this.raio = raio;
	}

	@Override
    public Object clone() {
    	try {
    		CirculoImpl clone = (CirculoImpl) super.clone();
    		clone.setCentro(this.centro.clone());
    		return clone;
    	} catch (CloneNotSupportedException e) {
    		return null;
    	}
    }
    
    @Override
    public String toString() {
    	return "Circulo (" +
    			getCentro() +
    			" " + getRaio() +
    			") ";
    }
    
}
