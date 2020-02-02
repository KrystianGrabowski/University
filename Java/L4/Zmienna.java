package wyrazenia;

import java.util.Arrays;

/**
 * Klasa przechowywująca zmienną
 */

public class Zmienna extends Wyrazenie {
	
	public static final Zbior zmienne;
	public String zmienna;
	
	static {
		zmienne = new Zbior(10);
	}
	
	public Zmienna(String zmienna) {
		this.zmienna = zmienna;

	}
	
	public static void dodaj_zmienna(String klucz, double wartosc) {
		Para para = new Para(klucz, wartosc);
		zmienne.ustal(para);
	}
	
	public double oblicz() {
		return zmienne.czytaj(zmienna);
	}
	
	public boolean equals(Object o) {
		if (o == null || this.getClass() != o.getClass()) {
			return false;
		}
		if (this == o) {
			return true;
		}
		Zmienna z = (Zmienna) o;
		if (this.zmienna == z.zmienna){
			return true;
		}
		return false;
	
	}
	
	public String toString() {
		return zmienna;
	}


}
