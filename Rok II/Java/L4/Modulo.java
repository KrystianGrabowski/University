package wyrazenia;

/**
 * Klasa licząca modulo 
 */
public class Modulo extends Operator2Arg {
	
	public Modulo(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() throws IllegalArgumentException {
		if (b.oblicz() == 0) {
			throw new IllegalArgumentException("Dzielnik równy zero!");
		}
		return a.oblicz() % b.oblicz();
	}
	
	public String toString() {
		return a + " mod " + b;
	}
}
