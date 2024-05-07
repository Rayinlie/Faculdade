package main;

public class application {

	public static void main(String[] args) {
		
		ObservableData pcd1 = new ObservableData(36.0, 7.0, 15.0);
		ObservableData pcd2 = new ObservableData(20.0, 14.0, 10.0);
		ObservableData pcd3 = new ObservableData(15.0, 1.0, 12.0);
		ObservableData pcd4 = new ObservableData(18.0, 0.0, 13.0);
		
		ConcreteObserver concOb1 = new ConcreteObserver("SP");
		ConcreteObserver concOb2 = new ConcreteObserver("MG");
		ConcreteObserver concOb3 = new ConcreteObserver("RJ");
		ConcreteObserver concOb4 = new ConcreteObserver("BA");
		ConcreteObserver concOb5 = new ConcreteObserver("DF");
		
		pcd1.add(concOb1);
		pcd1.add(concOb2);
		pcd1.add(concOb3);
		
		pcd2.add(concOb4);
		pcd2.add(concOb5);
		
		pcd3.add(concOb1);
		pcd3.add(concOb2);
		pcd3.add(concOb3);
		pcd3.add(concOb4);
		pcd3.add(concOb5);
		
		pcd4.add(concOb4);
		
		System.out.println("Alterando PCD1");
		pcd1.setPh(5.0);
		
		System.out.println("Alterando PCD2");
		pcd2.setTemp(40.0);
		
		System.out.println("Alterando PCD3");
		pcd3.setPa(4.0);
		
		System.out.println("Alterando PCD4");
		pcd4.setPa(1.0);
		pcd4.setPh(4.0);
		pcd4.setTemp(36.0);
				
		System.out.println("Removendo e atualizando PCD4");
		pcd4.remove(concOb4);
		pcd4.setPa(.5);
	}

}
