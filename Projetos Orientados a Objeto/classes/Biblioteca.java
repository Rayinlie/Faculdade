package classes;

import java.util.ArrayList;
import java.util.List;

public class Biblioteca {
    private static Biblioteca instancia;
    private List<Recurso> recursos;

    private Biblioteca() {
        recursos = new ArrayList<>();
    }

    public static Biblioteca getInstance() {
        if (instancia == null) {
            instancia = new Biblioteca();
        }
        return instancia;
    }

    public void adicionarRecurso(Recurso recurso) {
        recursos.add(recurso);
    }

    public Recurso buscarRecurso(String titulo) {
        for (Recurso recurso : recursos) {
            if (recurso.getTitulo().equals(titulo)) {
                return recurso;
            }
        }
        return null;
    }
}
