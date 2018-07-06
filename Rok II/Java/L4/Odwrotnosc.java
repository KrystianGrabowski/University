package wyrazenia;

/**
 * Klasa licząca odwrotność wyrażeń
 */
public class Odwrotnosc extends Operator1Arg {
	
	public Odwrotnosc(Wyrazenie a) {
		super(a);
	}
	
	public double oblicz() {
		return 1 / a.oblicz();
	}
	
	public String toString() {
		return "(" + a + ")^(-1)";
	}

}
