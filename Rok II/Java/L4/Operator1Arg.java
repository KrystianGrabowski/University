package wyrazenia;
/**
 * Klasa dla operatorów jednoargumentowych
 */


public abstract class Operator1Arg extends Wyrazenie {

	protected Wyrazenie a;
	
	public Operator1Arg(Wyrazenie a) {
		this.a = a;
	}
	
	public boolean equals(Object o) {
		if (o == null || this.getClass() != o.getClass()) {
			return false;
		}
		if (this == o) {
			return true;
		}
		Operator1Arg o1 = (Operator1Arg) o;
		if (this.a.equals(o1.a)){
			return true;
		}
		return false;
	
	}

}
