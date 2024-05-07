public class App {
    public static void main(String[] args) throws Exception {
        Texto texto = new Texto("Esse é um texto");

        // Teste do decorador de caixa alta
        CaixaAltaDecorator caixaAlta = new CaixaAltaDecorator(texto);
        System.out.println(caixaAlta.getTexto()); 

        // Teste do decorador invertido
        InvertidoDecorator invertido = new InvertidoDecorator(texto);
        System.out.println(invertido.getTexto()); 

        // Teste do decorador de tags
        TagDecorator tagDecorator = new TagDecorator(texto);
        System.out.println(tagDecorator.getTexto());
        
        // Teste de cascata de decoradores (caixa alta + invertido + tags)
        Texto textoCascata = new TagDecorator(new InvertidoDecorator(new CaixaAltaDecorator(texto)));
        System.out.println(textoCascata.getTexto());
    }
}
