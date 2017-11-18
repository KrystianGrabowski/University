package narzedzia;


/**
 * Klasa przechowywująca Parę klucz-wartosc (String-double)
 *
 */

public class Para<K,W> {
	public final K klucz;
	private W wartosc;

	public Para(K klucz, W wartosc){
		this.klucz = klucz;
		this.wartosc = wartosc;
	}

	public void ustaw(W wartosc){
		this.wartosc = wartosc;
	}

	public W pobierz(){
		return this.wartosc;
	}

	public String toString(){
		return "<" + this.klucz + "," + this.wartosc + ">";
	}
	public boolean equals(Object o){
		if (o == null){
			return false;
		}

		return (o instanceof Para && this.klucz.equals(((Para) o).klucz));


	}

}
