package Command;

import java.util.HashMap;
import java.util.Map;

class BancoPessoas {
    Map<Integer, Pessoa> pessoas = new HashMap<>();
    Map<String, Command> commands = new HashMap<>();

    BancoPessoas() {
        commands.put("new", args -> pessoas.put(Integer.parseInt(args[1]), new Pessoa(Integer.parseInt(args[1]), args[2])));
        commands.put("delete", args -> pessoas.remove(Integer.parseInt(args[1])));
        commands.put("all", args -> pessoas.values().forEach(p -> System.out.println(p.id + " " + p.nome)));
        commands.put("get", args -> {
            Pessoa p = pessoas.get(Integer.parseInt(args[1]));
            System.out.println(p.id + " " + p.nome);
        });
    }

    void handleCommand(String[] args) {
        Command command = commands.get(args[0]);
        if (command != null) {
            command.execute(args);
        } else {
            System.out.println("Comando desconhecido: " + args[0]);
        }
    }

    public static void main(String[] args) {
        BancoPessoas banco = new BancoPessoas();
        banco.handleCommand(args);
    }
}
