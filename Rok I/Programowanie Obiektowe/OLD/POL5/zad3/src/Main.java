import java.util.Hashtable;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		Hashtable<String, Integer> Krzy� = new Hashtable<String, Integer>();
		Krzy�.put("x",5);
		Krzy�.put("y",2);
		
		Hashtable<String, Integer> Sta� = new Hashtable<String, Integer>();
		Sta�.put("a",8);
		Sta�.put("h",109);

		
		Wyrazenie treee = new Dodaj(new Stala(2), new Zmienna("y", Krzy�));
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Dodaj(new Zmienna("a", Sta�), treee);
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Odejm(treee, new Stala(1));
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Pomnoz(new Stala(7), treee);
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Podziel(treee, new Zmienna("x", Krzy�));
		System.out.println(treee.toString() + " = " + treee.Oblicz());
		treee = new Dodaj(treee, new Stala(21));
		System.out.println(treee.toString() + " = " + treee.Oblicz());

	}

}
