package interfaces;

import classes.Recurso;

public interface Observador {
    void notificar(Recurso recurso);
}