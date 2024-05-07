package Factory;

import classes.Recurso;
import interfaces.FabricaRecurso;

public class FabricaLivro implements FabricaRecurso {
    @Override
    public Recurso criarRecurso(String titulo) {
        return new Recurso(titulo);
    }
}