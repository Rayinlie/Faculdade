package main;

import java.util.ArrayList;
import java.util.Iterator;

public class Observable {
	
	private ArrayList<Observer> observers = new ArrayList<>();

	public void add(Observer o) {
		observers.add(o);
	}
	
	public void remove(Observer o) {
		observers.remove(o);
	}
	
	public void notificar(String campo) {
		Iterator<Observer> it = observers.iterator();
		while(it.hasNext()) {
			Observer o = (Observer) it.next();
			o.update(this);
			System.out.println(o.toString() + " Atualizou o(a) " + campo);
		}
	}
}
