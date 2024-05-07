package classes;

import interfaces.EstadoRecurso;

public class EstadoEmprestado implements EstadoRecurso {
    private Usuario usuario;

    public EstadoEmprestado(Usuario usuario) {
        this.usuario = usuario;
    }

    @Override
    public void reservar(Recurso recurso, Usuario usuario) {
        System.out.println("Recurso " + recurso.getTitulo() + " está emprestado.");
    }

    @Override
    public void emprestar(Recurso recurso, Usuario usuario) {
        System.out.println("Recurso " + recurso.getTitulo() + " já está emprestado.");
    }

    @Override
    public void devolver(Recurso recurso, Usuario usuario) {
        if (this.usuario == usuario) {
            recurso.setEstado(new EstadoDisponivel());
            usuario.removerEmprestimo(recurso);
            recurso.notificarObservadores();
            System.out.println("Recurso " + recurso.getTitulo() + " devolvido pelo usuário " + usuario.getNome() + ".");
        } else {
            System.out.println("Recurso " + recurso.getTitulo() + " não foi emprestado para este usuário.");
        }
    }
}
