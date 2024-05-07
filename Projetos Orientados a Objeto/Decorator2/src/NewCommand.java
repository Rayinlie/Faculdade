import java.util.List;

class NewCommand implements Command {
    private String value;

    public NewCommand(String value) {
        this.value = value;
    }

    public void execute(List<String> elements) {
        System.out.println("Comando New: Inserindo valor '" + value + "'");
        elements.add(value);
    }
}
