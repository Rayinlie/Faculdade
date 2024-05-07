package classes;

import interfaces.EstadoRecurso;

public class EstadoReservado implements EstadoRecurso {
    private Usuario usuario;

    public EstadoReservado(Usuario usuario) {
        this.usuario = usuario;
    }

    @Override
    public void reservar(Recurso recurso, Usuario usuario) {
        System.out.println("Recurso " + recurso.getTitulo() + " já está reservado.");
    }

    @Override
    public void emprestar(Recurso recurso, Usuario usuario) {
        if (this.usuario == usuario) {
            recurso.setEstado(new EstadoEmprestado(usuario));
            usuario.adicionarEmprestimo(recurso);
            System.out.println("Recurso " + recurso.getTitulo() + " emprestado para o usuário " + usuario.getNome() + ".");
        } else {
            System.out.println("Recurso " + recurso.getTitulo() + " está reservado para outro usuário.");
        }
    }

    @Override
    public void devolver(Recurso recurso, Usuario usuario) {
        System.out.println("Recurso " + recurso.getTitulo() + " já está reservado.");
    }
}