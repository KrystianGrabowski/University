

public class Obiekt_Sportowy {
	public String nazwa;
	public String ulica;
	public Integer telefon;
	public Pracownicy P;
	public Klienci K;
	
	public boolean klient_k(String imie, String nazwisko)
	{
		return K.klient(imie, nazwisko);
	}

	public void wypisz_klientow(){
		System.out.print(K.ToStringK()) ;
	}
	
	public boolean pracuje_p(String imie, String nazwisko)
	{
		return P.zatrudniony(imie, nazwisko);
	}

	public void wypisz_pracownikow(){
		System.out.print(P.ToStringP()) ;
	}
	
	public void waznosc_karnetu(String imie, String nazwisko){
		System.out.print("Karnet wazny : " + K.ile_dni_wazny(imie, nazwisko) + " dni\n");
	}
	public void edycja(){
		K.Edycja();
	}

}
