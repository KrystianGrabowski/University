package wyrazenia;
/**
 * Klasa licząca arcus tangens
 */
public class Arctan extends Operator1Arg {
	
	public Arctan(Wyrazenie a) {
		super(a);
	}
	
	public double oblicz() {
		return Math.toDegrees(Math.atan(a.oblicz()));
	}
	
	public String toString() {
		return "arctan(" + a + ")";
	}

}
