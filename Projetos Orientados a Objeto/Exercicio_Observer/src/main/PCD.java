package main;

public class PCD {
	
	private Double temp;
	private Double ph;
	private Double pa;

	public PCD(Double temp, Double ph, Double pa) {
		this.temp = temp;
		this.ph = ph;
		this.pa = pa;
	}

	public Double getTemp() {
		return temp;
	}

	public void setTemp(Double temp) {
		this.temp = temp;
	}

	public Double getPh() {
		return ph;
	}

	public void setPh(Double ph) {
		this.ph = ph;
	}

	public Double getPa() {
		return pa;
	}

	public void setPa(Double pa) {
		this.pa = pa;
	}
	
}
