package wyrazenia;

/**
 * Klasa wybierająca maksimum
 */
public class Maksimum extends Operator2Arg {
	
	public Maksimum(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() throws IllegalArgumentException {
		return Math.max(a.oblicz() , b.oblicz());
	}
	
	public String toString() {
		return "max(" + a + ", " + b + ")";
	}
}
