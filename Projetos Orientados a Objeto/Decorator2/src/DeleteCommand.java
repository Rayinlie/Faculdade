import java.util.List;

class DeleteCommand implements Command {
    private String value;

    public DeleteCommand(String value) {
        this.value = value;
    }

    public void execute(List<String> elements) {
        System.out.println("Comando Delete: Removendo valor '" + value + "'");
        elements.remove(value);
    }
}
