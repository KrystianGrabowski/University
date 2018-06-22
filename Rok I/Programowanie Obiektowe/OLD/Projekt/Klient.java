
public class Klient extends Czlowiek {
	DataK DX;
	DataK DY;
	
	public Klient(String i, String n, String x, String y, int w, String p){
		imie = i;
		nazwisko = n;
		wiek = w;
		DX = new DataK(x);
		DY = new DataK(y);
		pesel = p;
	}
	
	public DataK KarnetP(){
		return DX;
	}
	
	public DataK KarnetK(){
		return DY;
	}
	
}
