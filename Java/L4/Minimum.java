package wyrazenia;

/**
 * Klasa wybierająca maksimum
 */
public class Minimum extends Operator2Arg {
	
	public Minimum(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() throws IllegalArgumentException {
		return Math.min(a.oblicz() , b.oblicz());
	}
	
	public String toString() {
		return "min(" + a + ", " + b + ")";
	}
}
