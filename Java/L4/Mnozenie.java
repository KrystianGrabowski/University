package wyrazenia;

/**
 * Klasa licząca iloczyn wyrażeń
 */
public class Mnozenie extends Operator2Arg {
	
	public Mnozenie(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() {
		return a.oblicz() * b.oblicz();
	}
	
	public String toString() {
		return "(" + a + "*" + b + ")";
	}
}
