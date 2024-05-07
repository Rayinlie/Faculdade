package implementation;

import interfaces.Circulo;
import interfaces.Ponto;

public class CirculoImpl implements Circulo {
  
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
    
    @Override
    public String toString() {
    	return "Circulo (" +
    			getCentro() +
    			" " + getRaio() +
    			") ";
    }
    
}
