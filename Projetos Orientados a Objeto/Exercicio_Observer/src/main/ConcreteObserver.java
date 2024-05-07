package main;

public class ConcreteObserver implements Observer {
	
	private String nome;
	
	public ConcreteObserver(String nome) {
		this.nome = nome;
	}

	@Override
	public void update(Observable o) {
		ObservableData data = (ObservableData) o;
		data.getData();
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}
	
	@Override
	public String toString() {
		return this.getNome();
	}

}
