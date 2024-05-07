package implementation;

import interfaces.Ponto;

public class PontoImpl implements Ponto, Cloneable {

    private int x;
    private int y;
    
    public PontoImpl(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    public int getX() {
        return x;
    }
    
    public int getY() {
        return y;
    }
    
    public Ponto clone() {
    	try {
    		return (Ponto) super.clone();
    	} catch (CloneNotSupportedException e) {
    		return null;
    	}
    }
    
    @Override
    public String toString() {
    	return "Ponto (" +
    			getX() +
    			" " + getY() +
    			") ";
    }
}