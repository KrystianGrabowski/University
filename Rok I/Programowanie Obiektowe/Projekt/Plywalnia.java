import java.io.FileNotFoundException;
import java.util.Objects;


public class Plywalnia extends Obiekt_Sportowy {
	public Pracownicy P;
	public Klienci K;
	public int nr_lokalu;
	public String zapisP = "pracownicyP.txt", zapisK = "klienciP.txt";
	public Plywalnia(String n, String u, int nr, Integer t)
	{
		K = new Klienci(zapisK);
		P = new Pracownicy();
		nazwa = n;
		ulica = u;
		nr_lokalu = nr;
		telefon = t;
		wczytaj("Pracownicy");
		wczytaj("Klienci");

	}

	public String nazwa()
	{
		return "Witamy w plywalni " + nazwa;
	}
	public String kontakt()
	{
		return "Kontakt do plywalni " + nazwa + " -> " + telefon;
	}
	
	
	
	
	public void dodaj_k(String imie, String nazwisko, String datax, String datay, int wiek , String pesel)
	{
		K.dodaj(imie, nazwisko, datax, datay, wiek, pesel);
		zapisz("Klienci");
	}
	
	public void usun_k(String imie, String nazwisko)
	{
		K.usun(imie, nazwisko);
		zapisz("Klienci");
	}
	
	public void przedluz_karnet(String imie, String nazwisko, Integer dni){
		K.przedluz(imie, nazwisko, dni);
		zapisz("Klienci");
	}
	

	
	public void dodaj_p(String imie, String nazwisko, String stanowisko, int wiek , String pesel)
	{
		P.dodaj(imie, nazwisko, stanowisko, wiek, pesel);
		zapisz("Pracownicy");
	}
	
	public void usun_p(String imie, String nazwisko)
	{
		P.usun(imie, nazwisko);
		zapisz("Pracownicy");
	}
	
	
	
	public void zapisz(String T){
		try {
			if (Objects.equals(T, "Pracownicy" )){
				P.WriteToFile(zapisP);				
			}
			else{
				K.WriteToFile(zapisK);
			}

		} catch (FileNotFoundException e) {
			System.out.println("NIE ZNAEZIONO PLIKU");
		}
	}
	public void wczytaj(String T){
		try {
			if (Objects.equals(T, "Pracownicy" )){
				P.ReadFromFile(zapisP);				
			}
			else{
				K.ReadFromFile(zapisK);
			}

		} 
		catch (FileNotFoundException e) {
			System.out.println("NIE ZNAEZIONO PLIKU");
		}

	}
}
