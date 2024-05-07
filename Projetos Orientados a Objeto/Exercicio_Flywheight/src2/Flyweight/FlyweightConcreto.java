package Flyweight;

public class FlyweightConcreto implements Flyweight{

	private Integer algorismo;
	
	public FlyweightConcreto(Integer algorismo) {
		this.algorismo = algorismo;
	}

	public Integer getAlg() {
		return algorismo;
	}

	@Override
	public void operacao() {
		System.out.println(algorismo);
	}

	@Override
	public String toString() {
		return algorismo.toString();
	}
	
}
