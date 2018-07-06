package wyrazenia;

/**
 * Klasa logarytmująca
 */
public class Logarytmowanie extends Operator2Arg {
	
	public Logarytmowanie(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() throws IllegalArgumentException {
		if (a.oblicz() < 2 || b.oblicz() < 0){
			throw new IllegalArgumentException("Błędne dane do logarytmu");
		}
		return Math.log(a.oblicz()) / Math.log(b.oblicz());
	}
	
	public String toString() {
		return "log(" + a + ", " + b + ")";
	}
}
