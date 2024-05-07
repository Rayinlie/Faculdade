package interfaces;

public interface FabricaDeFormas {

	Ponto criarPonto(int x, int y);
	Circulo criarCirculo(Ponto ponto, int raio);
	Retangulo criarRetangulo(Ponto ponto1, Ponto ponto2);
	Triangulo criarTriangulo(Ponto ponto1, Ponto ponto2, Ponto ponto3);

}