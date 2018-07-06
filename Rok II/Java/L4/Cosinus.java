package wyrazenia;
/**
 * Klasa licząca arcus cosinus
 */

public class Cosinus extends Operator1Arg {
	
	public Cosinus(Wyrazenie a) {
		super(a);
	}
	
	public double oblicz() {
		return Math.cos(Math.toRadians(a.oblicz()));
	}
	
	public String toString() {
		return "cos(" + a + ")";
	}

}
