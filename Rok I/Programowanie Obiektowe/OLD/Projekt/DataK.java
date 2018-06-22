
public class DataK {
	int rok,miesiac,dzien;
	public DataK (int r, int m, int d){
		rok = r;
		miesiac = m;
		dzien = d;
	}
	
	public DataK (String data){
		String T[] = data.split("-");
		rok = Integer.valueOf(T[0]);
		miesiac = Integer.valueOf(T[1]);
		dzien = Integer.valueOf(T[2]);
	}
	
	public int _rok(){
		return rok;
	}
	public int _miesiac(){
		return miesiac;
	}
	public int _dzien(){
		return dzien;
	}

}
