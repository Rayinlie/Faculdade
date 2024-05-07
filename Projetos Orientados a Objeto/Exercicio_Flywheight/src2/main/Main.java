package main;

import java.util.ArrayList;
import java.util.Random;

import Factory.FlyFactory;
import Flyweight.FlyweightConcreto;

public class Main {
	
	public static void main(String[] args) {
		
		Random rand = new Random();
		
		FlyFactory flyFactory = new FlyFactory();
		
		FlyweightConcreto fly = null;
		
		for(int i=0; i<10; i++) {
			for(int j=0; j<10; j++) {
				fly = flyFactory.operacaoFactory(rand.nextInt(0, 9));
				System.out.print(fly.toString());
			}
			System.out.println();
		}
	}

}
