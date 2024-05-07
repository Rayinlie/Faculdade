package main;

import docs.Planilha;
import docs.Texto;
import funcs.GerarHTML;
import funcs.GerarTexto;
import funcs.GerarXML;
import funcs.Validar;
import interfaces.Documento;

public class Cliente {
	
	public static void main(String[] args) {
	
		Documento doc = new Texto();
		doc.aceitar(new GerarTexto());
		doc.aceitar(new GerarHTML());
		doc.aceitar(new GerarXML());
		if (((Boolean)doc.aceitar(
				new Validar())).booleanValue()) {
			System.out.println(doc + " valido!");
		}
		
		System.out.println();
		
		Documento doc_2 = new Planilha();
		doc.aceitar(new GerarTexto());
		doc.aceitar(new GerarHTML());
		doc.aceitar(new GerarXML());
		if (((Boolean)doc.aceitar(
				new Validar())).booleanValue()) {
			System.out.println(doc_2 + " valido!");
		}
	}
}