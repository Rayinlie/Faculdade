package Factory;

import java.util.HashMap;
import java.util.Map;

import Flyweight.Flyweight;
import Flyweight.FlyweightConcreto;

public class FlyFactory {
	
	private Map<Integer, Flyweight> lista;

	public FlyFactory() {
		lista = new HashMap<>();
	}
	
	public FlyweightConcreto operacaoFactory(Integer id) {
		if(lista.containsKey(id)) {
			return (FlyweightConcreto) lista.get(id);
		}else {
			Flyweight fly = new FlyweightConcreto(id);
			lista.put(id, fly);
			return (FlyweightConcreto) fly;
		}
	}
	
}
