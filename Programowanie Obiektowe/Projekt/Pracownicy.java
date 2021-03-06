import java.util.ArrayList;
import java.util.Objects;
import java.io.File;
import java.io.Serializable;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;


public class Pracownicy implements Serializable  {
	
	private static final long serialVersionUID = 1L;
	public ArrayList <Pracownik> pracownicy = new ArrayList <Pracownik>();
	
	public void dodaj(String imie, String nazwisko, String stanowisko, int wiek, String pesel)
	{
		Pracownik P = new Pracownik(imie,nazwisko,stanowisko,wiek,pesel);
		pracownicy.add(P);
	}
	public boolean zatrudniony(String imie, String nazwisko)
	{
		for (int i=0; i<pracownicy.size(); i++)
		{

			if (Objects.equals((pracownicy.get(i).imie), imie))
			{
				if (Objects.equals((pracownicy.get(i).nazwisko), nazwisko))
				{
					return true;
				}
			}
		}

		return false;
	}
	
	public void usun(String imie, String nazwisko)
	{
		if (zatrudniony(imie,nazwisko) == true)
		{
			for (int i=0; i<pracownicy.size(); i++)
			{
				if (Objects.equals((pracownicy.get(i).imie), imie))
				{

					if (Objects.equals((pracownicy.get(i).nazwisko), nazwisko))
					{
						pracownicy.remove(i);
					}
				}
			}
		}
		else
		{
			System.out.println("Nie znaleziono pracownika " + imie + " " + nazwisko);
		}
	}
	
	public String ToStringP(){
		String lista = "";
		for (int i=0; i<pracownicy.size(); i++)
		{
			Pracownik p = pracownicy.get(i);
			lista = lista + p.imie + " " + p.nazwisko +  " " + p.stanowisko + " " + p.wiek + " " + p.pesel ;
			lista = lista + "\n";
		}
		return lista;
		
	}
	public void WriteToFile(String nazwa) throws FileNotFoundException{
		PrintWriter zapis = new PrintWriter(nazwa);
		String pracownicy = ToStringP();
		zapis.print(pracownicy);
		zapis.close();
	}
	public void ReadFromFile(String nazwa) throws FileNotFoundException{
		File plik = new File(nazwa);
		Scanner odczyt = new Scanner(plik);

		while(odczyt.hasNext())
		{
			String linia = odczyt.nextLine();
			String T[] = linia.split(" ");
			int wiek = Integer.valueOf(T[3]);
			dodaj(T[0],T[1],T[2],wiek,T[4]);
		}
		odczyt.close();
	}
	
}
