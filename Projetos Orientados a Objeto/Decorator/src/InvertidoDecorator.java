class InvertidoDecorator extends Texto {
    public InvertidoDecorator(Texto texto) {
        super(new StringBuilder(texto.getTexto()).reverse().toString());
    }
}