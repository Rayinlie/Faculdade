class TagDecorator extends Texto {
    public TagDecorator(Texto texto) {
        super("<b>" + texto.getTexto() + "</b>");
    }
}
