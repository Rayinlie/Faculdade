import java.util.List;

class GetCommand implements Command {
    private int index;

    public GetCommand(int index) {
        this.index = index;
    }

    public void execute(List<String> elements) {
        if (index >= 0 && index < elements.size()) {
            String value = elements.get(index);
            System.out.println("Comando Get: Obtendo valor no índice " + index + ": '" + value + "'");
        } else {
            System.out.println("Comando Get: Índice inválido.");
        }
    }
}
