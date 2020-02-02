package wyrazenia;

/**
 * Klasa przechowywująca stałą
 */

public class Stala extends Wyrazenie {

	double wartosc;	
	
	public Stala(double wartosc) {
		this.wartosc = wartosc;
	}
	
	public double oblicz(){
		return wartosc;
	}
	
	public String toString() {
		return String.valueOf(wartosc);
	}
	
	public boolean equals(Object o) {

		if (o == null || this.getClass() != o.getClass()) {
			return false;
		}
		if (this == o) {
			return true;
		}
		Stala s = (Stala) o;
		if (this.wartosc == s.wartosc){
			return true;
		}
		return false;
	
	}
	
	

}
