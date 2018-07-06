package geometria;

public class Odcinek{
	
	public Punkt PunktA;
	public Punkt PunktB;
	
	public Odcinek(double x1, double y1, double x2, double y2){
		try{
			if(x1 == x2 && y1 == y2)
			{
				throw new IllegalArgumentException();
			}	
		
			PunktA = new Punkt(x1,y1);
			PunktB = new Punkt(x2,y2); 		
		}
		catch (IllegalArgumentException e){
			System.out.println("Podano takie same punkty dla odcinka !");
		
		}
	}
	public void przesun(Wektor v){
		PunktA.przesun(v);
		PunktB.przesun(v);
	}
	
	public void obroc(Punkt p, double kat){
		PunktA.obroc(p, kat);
		PunktB.obroc(p, kat);
	}
	
	public void odbij(Prosta p){
		
		PunktA.odbij(p);
		PunktB.odbij(p);
	}

	public void wypisz(){
		PunktA.wypisz();
		PunktB.wypisz();
	}

}
