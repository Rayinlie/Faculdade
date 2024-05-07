package classes;

import java.util.ArrayList;
import java.util.List;
import interfaces.Observador;

public class Usuario implements Observador {
    private String nome;
    private List<Recurso> emprestimos;

    public Usuario(String nome) {
        this.nome = nome;
        this.emprestimos = new ArrayList<>();
    }

    @Override
    public void notificar(Recurso recurso) {
        System.out.println("Usuário " + nome + " foi notificado que o recurso " + recurso.getTitulo() + " está disponível.");
    }

    public void adicionarEmprestimo(Recurso recurso) {
        emprestimos.add(recurso);
    }

    public void removerEmprestimo(Recurso recurso) {
        emprestimos.remove(recurso);
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public List<Recurso> getEmprestimos() {
        return emprestimos;
    }

    public void setEmprestimos(List<Recurso> emprestimos) {
        this.emprestimos = emprestimos;
    }

}