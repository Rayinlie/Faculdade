package implementation;

import interfaces.Circulo;
import interfaces.FabricaDeFormas;
import interfaces.Ponto;
import interfaces.Retangulo;
import interfaces.Triangulo;

public class FabricaDeFormasImpl implements FabricaDeFormas {
    public Ponto criarPonto(int x, int y) {
        return new PontoImpl(x, y);
    }
    
    public Circulo criarCirculo(Ponto ponto, int raio) {
        return new CirculoImpl(ponto, raio);
    }
    
    public Retangulo criarRetangulo(Ponto ponto1, Ponto ponto2) {
        return new RetanguloImpl(ponto1, ponto2);
    }
    
    public Triangulo criarTriangulo(Ponto ponto1, Ponto ponto2, Ponto ponto3) {
        return new TrianguloImpl(ponto1, ponto2, ponto3);
    }
}