public class CaixaAltaDecorator extends Texto {
    public CaixaAltaDecorator(Texto texto) {
        super(texto.getTexto().toUpperCase());
    }
}