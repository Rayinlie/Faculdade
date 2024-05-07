package concretas;

import interfaces.Estrategia;

public class nullObj implements Estrategia{
    @Override
    public void movimento() {
        System.out.println("NULL");
    }

    @Override
    public void concluir() {
        System.out.println("NULL");    
    }
}