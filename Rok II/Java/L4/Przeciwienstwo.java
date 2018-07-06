package wyrazenia;

/**
 * Klasa obliczająca przeciwieństwo wyrażęnia
 */

public class Przeciwienstwo extends Operator1Arg {
	
	public Przeciwienstwo(Wyrazenie a) {
		super(a);
	}
	
	public double oblicz() {
		return a.oblicz() * (-1);
	}
	
	public String toString() {
		return "-(" + a + ")";
	}
}
