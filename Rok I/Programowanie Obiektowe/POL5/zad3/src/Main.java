import java.util.Hashtable;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		Hashtable<String, Integer> Krzyœ = new Hashtable<String, Integer>();
		Krzyœ.put("x",5);
		Krzyœ.put("y",2);
		
		Hashtable<String, Integer> Staœ = new Hashtable<String, Integer>();
		Staœ.put("a",8);
		Staœ.put("h",109);

		
		Wyrazenie treee = new Dodaj(new Stala(2), new Zmienna("y", Krzyœ));
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Dodaj(new Zmienna("a", Staœ), treee);
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Odejm(treee, new Stala(1));
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Pomnoz(new Stala(7), treee);
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Podziel(treee, new Zmienna("x", Krzyœ));
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Dodaj(treee, new Stala(21));
		System.out.println(treee.toString() + " = " + treee.Oblicz());

	}

}
