package Factory2;

import java.util.HashMap;
import java.util.Map;

import Flyweight2.Flyweight2;
import Flyweight2.FlyweightConcreto2;

public class FlyFactory2 {
	
	private Map<Integer, Flyweight2> lista;

	public FlyFactory2() {
		lista = new HashMap<>();
	}
	
	public FlyweightConcreto2 operacaoFactory(Integer id) {
		if(lista.containsKey(id)) {
			return (FlyweightConcreto2) lista.get(id);
		}else {
			Flyweight2 fly = new FlyweightConcreto2(id);
			lista.put(id, fly);
			return (FlyweightConcreto2) fly;
		}
	}
	
}
