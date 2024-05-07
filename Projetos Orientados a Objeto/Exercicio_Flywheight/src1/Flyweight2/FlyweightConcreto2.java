package Flyweight2;

public class FlyweightConcreto2 implements Flyweight2 {

	private Integer algorismo;
	
	public FlyweightConcreto2(Integer algorismo) {
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
