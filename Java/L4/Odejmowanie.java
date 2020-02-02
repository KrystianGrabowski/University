package wyrazenia;

/**
 * Klasa licząca różnicę wyrażęń
 */
public class Odejmowanie extends Operator2Arg {
	
	public Odejmowanie(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() {
		return a.oblicz() - b.oblicz();
	}
	
	public String toString() {
		return "(" + a + "-" + b + ")";
	}
}
