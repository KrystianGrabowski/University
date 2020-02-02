package wyrazenia;
/**
 * Klasa licząca sumę wyrażeń
 */
public class Dodawanie extends Operator2Arg {
	
	public Dodawanie(Wyrazenie a, Wyrazenie b) {
		super(a,b);
	}
	
	public double oblicz() {
		return a.oblicz() + b.oblicz();
	}
	
	public String toString() {
		return "(" + a + "+" + b + ")";
	}
}
