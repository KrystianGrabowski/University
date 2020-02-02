package wyrazenia;

/**
 * Klasa wyliczająca wartość bezwzględną wyrażenia
 */

public class WartBezwzgl extends Operator1Arg {
	
	public WartBezwzgl (Wyrazenie a) {
		super(a);
	}
	
	public double oblicz() {
		return Math.abs(a.oblicz());
	}
	
	public String toString() {
		return "|" + a + "|";
	}
}
