package main;

import concreto.Manga;
 
public class Main {

	public static void main(String[] args) {
		
		Manga manga = new Manga();
		
		manga.setEstado(manga.PRE);
		manga.printEmocao();

		manga.setEstado(manga.LANCANDO);
		manga.printEmocao();
		
		manga.setEstado(manga.HIATO);
		manga.printEmocao();
	
		manga.setEstado(manga.NULLOBJ);
		manga.printEmocao();
	}

}
