package narzedzia;

/**
 * Klasa dla przechowywyjąca parę klucz-wartość
 */

public class Para {

	public final String key;
	private double value;

	public Para(String key, double value) {
		this.key = key;
		this.value = value;
	}

	public double getValue() {
		return value;
	}

	public void setValue(double value) {
		this.value = value;
	}

	public String toString(){
		return "< " + key + "," + value + " >";
	}

	public boolean equals(Object o) {
		if (o == null) {
			return false;
		}

		if (this.key.equals(o)){
			return true;
		}
		return false;
	}
}
