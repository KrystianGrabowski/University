package wyrazenia;

/**
 * Klasa obliczająca sinus
 */

public class Sinus extends Operator1Arg {
	
	public Sinus(Wyrazenie a) {
		super(a);
	}
	
	public double oblicz() {
		return Math.sin(Math.toRadians(a.oblicz()));
	}
	
	public String toString() {
		return "sin(" + a + ")";
	}

}
