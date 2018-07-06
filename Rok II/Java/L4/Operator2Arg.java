package wyrazenia;

/**
 * Klasa dla operatorów dwuargumentowych
 */

public abstract class Operator2Arg extends Operator1Arg {
	
	protected Wyrazenie b;
	
	public Operator2Arg (Wyrazenie a, Wyrazenie b) {
		super(a);
		this.b = b;
	}
	public boolean equals(Object o) {
		if (o == null || this.getClass() != o.getClass()) {
			return false;
		}
		if (this == o) {
			return true;
		}
		Operator2Arg o2 = (Operator2Arg) o;

		if (this.a.equals(o2.a) && this.b.equals(o2.b)) {
			return true;
		}
		return false;
	
	}

}
