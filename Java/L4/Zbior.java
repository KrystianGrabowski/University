package wyrazenia;
import java.util.Arrays;

/**
 * Klasa przechowywyjąca zbiór par
 */

public class Zbior {

	private Para[] tablica;
	private int wielkosc;
	private int aktualny_rozmiar;
	
	public Zbior() {
		this.tablica = new Para[5];
		this.wielkosc = 5;
		aktualny_rozmiar = 0;
	}
	
	public Zbior(int n) {
		if (n >= 0) {
			this.tablica = new Para[n];
			this.wielkosc = n;
			aktualny_rozmiar = 0;
		}
		else {
			throw new NegativeArraySizeException();
		}
	}

	/** metoda szuka pary z określonym kluczem */
	public Para szukaj (String kl) {
		for (int i = 0; i < aktualny_rozmiar; i++) {
			if (tablica[i].key == kl)
				return tablica[i];
		}
		return null;
	}

	/** metoda wstawia do zbioru nową parę */
	public void wstaw (Para p) throws IllegalArgumentException {
		if (aktualny_rozmiar < wielkosc) {
			if (szukaj(p.key) == null) {
				tablica[aktualny_rozmiar] = p;
				aktualny_rozmiar += 1;
			}
		}
		else {
			//throw new IllegalArgumentException("tablica pełna");

		}
	}
	
	/** metoda odszukuje parę i zwraca wartość związaną z kluczem */
	public double czytaj (String kl) throws IllegalArgumentException {
		if (szukaj(kl) == null) {
			throw new IllegalArgumentException("Brak podanego klucza w zbiorze");
		}
		else {
			return szukaj(kl).getValue();
		}
	}
	
	/** metoda wstawia do zbioru nową albo aktualizuje istniejącą parę */
	public void ustal (Para p) throws IllegalArgumentException {
		if (szukaj(p.key) == null) {
			wstaw(p);
		}
		else {
			szukaj(p.key).setValue(p.getValue());
		}
	}
	
	/** metoda podaje ile par jest przechowywanych w zbiorze */
	public int ile () {
		return aktualny_rozmiar;
	}
	
	/** metoda usuwa wszystkie pary ze zbioru */
	public void czysc () {
		this.tablica = new Para[wielkosc];
		aktualny_rozmiar = 0; 
	}
	
	public String toString() {
		return Arrays.toString(tablica);
	}	
	


}
