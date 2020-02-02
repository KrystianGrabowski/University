package wyrazenia;

/**
 * Klasa licząca iloraz wyrażeń
 */
public class Dzielenie extends Operator2Arg {
	
	public Dzielenie(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() throws IllegalArgumentException {
		if (b.oblicz() == 0) {
			throw new IllegalArgumentException("Dzielnik równy zero!");
		}
		
		return a.oblicz() / b.oblicz();

		
	}
	
	public String toString() {
		return "(" + a + "/" + b + ")";
	}
}
