package wyrazenia;

/**
 * Klasa potęgująca wyrażenia
 */

public class Potegowanie extends Operator2Arg {
	
	public Potegowanie(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() {
		return Math.pow(a.oblicz(), b.oblicz());
	}
	
	public String toString() {
		return "(" + a + ")" + "^" + "(" + b + ")";
	}
}
