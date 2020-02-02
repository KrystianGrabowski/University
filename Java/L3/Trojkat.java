package geometria;

public class Trojkat{

	/*public Odcinek OdcinekA;  // x1 y1 1
	public Odcinek OdcinekB;  // x2 y2 1 
	public Odcinek OdcinekC;  // x3 y3 1*/

	public Punkt PunktA;  // x1 y1 1
	public Punkt PunktB;  // x2 y2 1 
	public Punkt PunktC;  // x3 y3 1	
	
	public Trojkat(double x1, double y1, double x2, double y2, double x3, double y3){
	
		try{
			double det;
			det = (x1 * y2) + (x2 * y3) + (x3 * y1) -
			 	  (y2 * x3) - (y3 * x1) - (y1 * x2);
			 	  
			if (det == 0){
				throw new IllegalArgumentException(); 
			}
		PunktA = new Punkt(x1,y1);
		PunktB = new Punkt(x2,y2);  
		PunktC = new Punkt(x3,y3);	
		}
		catch (IllegalArgumentException e){
			System.out.println("Podane trzy punkty są współliniowe !");
		}
		
		
		
	}
	public void przesun(Wektor v){
		PunktA.przesun(v);
		PunktB.przesun(v);
		PunktC.przesun(v); 	
	}
	
	public void obroc(Punkt p, double kat){
		PunktA.obroc(p ,kat);
		PunktB.obroc(p, kat);
		PunktC.obroc(p, kat);
	}
	
	public void odbij(Prosta p){
		PunktA.odbij(p);
		PunktB.odbij(p);
		PunktC.odbij(p); 
	}
	

	public void wypisz(){
		PunktA.wypisz();
		PunktB.wypisz();
		PunktC.wypisz();
		
			
	}

}
