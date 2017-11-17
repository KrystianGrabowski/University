package narzedzia;


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
		if (o == null || this.getClass() != o.getClass()) {
			return false;
		}

		if (this == o) {
			return true;
		}
		Para para = (Para) o;
		if (this.key.equals(para.key)){
			return true;
		}
		return false;
	}
}
