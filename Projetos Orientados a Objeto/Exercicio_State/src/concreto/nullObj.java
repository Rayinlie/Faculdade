package concreto;

import interfaces.Estado;

public class nullObj implements Estado{

    @Override
    public void printEmocao() {
        System.out.println("NULL");
    }
    
}
