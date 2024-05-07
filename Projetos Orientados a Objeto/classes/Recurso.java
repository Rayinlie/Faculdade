package classes;

import java.util.ArrayList;
import java.util.List;

import interfaces.EstadoRecurso;
import interfaces.Observador;

public class Recurso {
    private String titulo;
    private EstadoRecurso estado;
    private List<Observador> observadores;

    public Recurso(String titulo) {
        this.titulo = titulo;
        this.estado = (EstadoRecurso) new EstadoDisponivel();
        this.observadores = new ArrayList<>();
    }

    public String getTitulo() {
        return titulo;
    }

    public void reservar(Usuario usuario) {
        estado.reservar(this, usuario);
    }

    public void emprestar(Usuario usuario) {
        estado.emprestar(this, usuario);
    }

    public void devolver(Usuario usuario) {
        estado.devolver(this, usuario);
    }

    public void adicionarObservador(Observador observador) {
        observadores.add(observador);
    }

    public void removerObservador(Observador observador) {
        observadores.remove(observador);
    }

    public void notificarObservadores() {
        for (Observador observador : observadores) {
            observador.notificar(this);
        }
    }

    public void setEstado(EstadoEmprestado estadoEmprestado) {
        this.estado = estadoEmprestado;
    }

    public void setEstado(EstadoDisponivel estadoDisponivel) {
        this.estado = estadoDisponivel;
    }

    public void setEstado(EstadoReservado estadoReservado) {
        this.estado = estadoReservado;
    }
}
