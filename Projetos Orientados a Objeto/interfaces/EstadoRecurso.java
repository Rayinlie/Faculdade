package interfaces;

import classes.Recurso;
import classes.Usuario;

public interface EstadoRecurso {
    void reservar(Recurso recurso, Usuario usuario);
    void emprestar(Recurso recurso, Usuario usuario);
    void devolver(Recurso recurso, Usuario usuario);
}