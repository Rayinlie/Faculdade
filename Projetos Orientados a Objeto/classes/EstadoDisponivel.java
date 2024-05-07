package classes;

import interfaces.EstadoRecurso;

public class EstadoDisponivel implements EstadoRecurso {
    @Override
    public void reservar(Recurso recurso, Usuario usuario) {
        recurso.setEstado(new EstadoReservado(usuario));
        System.out.println("Recurso " + recurso.getTitulo() + " reservado para o usuário " + usuario.getNome() + ".");
    }

    @Override
    public void emprestar(Recurso recurso, Usuario usuario) {
        recurso.setEstado(new EstadoEmprestado(usuario));
        usuario.adicionarEmprestimo(recurso);
        System.out.println("Recurso " + recurso.getTitulo() + " emprestado para o usuário " + usuario.getNome() + ".");
    }

    @Override
    public void devolver(Recurso recurso, Usuario usuario) {
        System.out.println("Recurso " + recurso.getTitulo() + " já está disponível.");
    }
}