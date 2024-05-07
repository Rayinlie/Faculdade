import java.util.List;

class GetAllCommand implements Command {
    public void execute(List<String> elements) {
        System.out.println("opa");
        System.out.println("Comando GetAll: Exibindo todos os elementos:");
        for (int i = 0; i < elements.size(); i++) {
            String value = elements.get(i);
            System.out.println("Índice " + i + ": " + value);
        }
    }
}
