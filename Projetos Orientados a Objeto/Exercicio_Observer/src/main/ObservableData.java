package main;

public class ObservableData extends Observable {
	
	private Double temp;
	private Double ph;
	private Double pa;

	public ObservableData(Double temp, Double ph, Double pa) {
		this.temp = temp;
		this.ph = ph;
		this.pa = pa;
	}

	public Double getTemp() {
		return temp;
	}

	public void setTemp(Double temp) {
		this.temp = temp;
		notificar("Temperatura");
	}

	public Double getPh() {
		return ph;
	}

	public void setPh(Double ph) {
		this.ph = ph;
		notificar("PH");
	}

	public Double getPa() {
		return pa;
	}

	public void setPa(Double pa) {
		this.pa = pa;
		notificar("PA");
	}
	
	public ObservableData getData() {
		return this;
	}
}


