
import java.util.ArrayList;
import java.util.Collections;

public class Main 
{
	public static void main(String[] args) 
	{
		Kolekcja <String, Integer> kol = new Kolekcja<String, Integer>();
		kol.Dodaj("jas", 45);
		kol.Dodaj("stas", 11111);
		kol.Dodaj("krzys", 3);
		kol.Dodaj("adam", 1);
		kol.Dodaj("pawel", 523);

		kol.Wypisz();
		System.out.println("---------------");
		System.out.println(kol.Pobierz().key + " Pobrany");
		System.out.println(kol.Pobierz().key + " Pobrany");
		System.out.println(kol.Pobierz().key + " Pobrany");
		kol.Dodaj("dasaasd", 1);
		System.out.println("---------------");
		kol.Wypisz();
		System.out.println("-----------------");
		System.out.println("Hierarchia Klas:\n");
		ArrayList<StPolicja> Spis = new ArrayList <StPolicja>();
		Spis.add(new Inspektor("Malinowski"));
		Spis.add(new Komisarz("Kapusta"));
		Spis.add(new Posterunkowy("Kowalski"));
		Spis.add(new Seirzant("Andrzej"));
		Spis.add(new Komisarz("Pawlowicz"));
		
			Collections.sort(Spis);
		for(StPolicja p : Spis) System.out.println(p);

	}
}
