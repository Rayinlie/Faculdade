import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

public class App {
    public static void main(String[] args) throws Exception {

        
        // Criando o ComandoReader com um StringReader para simular a entrada
        ComandoReader comandoReader = new ComandoReader(new StringReader("new Franklin\nnew Trevor\nall\nget 0\ndelete Franklin\nall"));


        // Criando um objeto para armazenar os elementos
        List<String> elements = new ArrayList<>();

        // Processando os comandos
        try {
            List<Command> comandos = comandoReader.readComandos();
            for (Command comando : comandos) {
                comando.execute(elements);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }


    }
}
