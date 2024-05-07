import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

class ComandoReader extends Reader {
    private BufferedReader reader;

    public ComandoReader(Reader reader) {
        this.reader = new BufferedReader(reader);
    }

    public List<Command> readComandos() throws IOException {
        List<Command> commands = new ArrayList<>();
        String line;
        while ((line = reader.readLine()) != null) {
            String[] parts = line.trim().split("\\s+", 2);
            if (parts.length > 0) {
                String comando = parts[0];
                if (comando.equals("new") && parts.length > 1) {
                    String value = parts[1];
                    commands.add(new NewCommand(value));
                } else if (comando.equals("delete") && parts.length > 1) {
                    String value = parts[1];
                    commands.add(new DeleteCommand(value));
                } else if (comando.equals("get") && parts.length > 1) {
                    try {
                        int index = Integer.parseInt(parts[1]);
                        commands.add(new GetCommand(index));
                    } catch (NumberFormatException e) {
                        // Formato de índice inválido
                    }
                } else if (comando.equals("all")) {
                    commands.add(new GetAllCommand());
                }
            }
        }
        return commands;
    }

    @Override
    public int read(char[] cbuf, int off, int len) throws IOException {
        throw new UnsupportedOperationException("read(char[] cbuf, int off, int len) não é suportado.");
    }

    @Override
    public void close() throws IOException {
        reader.close();
    }
}