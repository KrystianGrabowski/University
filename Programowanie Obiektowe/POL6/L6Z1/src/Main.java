import java.io.FileNotFoundException;
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

        Slownik<String, Integer> slow = new Slownik<String, Integer>();
        slow.Dodaj("ala", 3);
        slow.Dodaj("kot", 123);
        slow.Dodaj("krzys", 1211231231);
        slow.Dodaj("stanislaw", 231);
        slow.Dodaj("jacek", 221111);
        /*try {
			slow.WriteToFile();
		} catch (FileNotFoundException e) {
		
			System.out.println("KKKKKKKKKK");
		}*/
        Slownik<String, Integer> s = new Slownik<String, Integer>();
		try {
			
			Slownik <String,Integer> C = s.ReadFromFile("/Users/Krystian/workspace/L6Z1/Slownik.txt");
			C.Wypisz();
		} catch (FileNotFoundException e) {}
		
        /*System.out.println(slow.Szukaj("ala"));
        slow.Usun("ala");
        slow.Dodaj("krzys", 1211231231);
        System.out.println(slow.Szukaj("krzys"));
        System.out.println(slow.Szukaj("ala"));
        System.out.println(slow.Szukaj("stanislaw"));*/


	}

}