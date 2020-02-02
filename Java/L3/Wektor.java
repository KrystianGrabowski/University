package geometria;

public class Wektor{

	public final double dx;
	public final double dy;
	
	public Wektor(double ax, double by){
		dx = ax;
		dy = by;
	
	}
	
	public static Wektor zloz(Wektor a, Wektor b){
		return new Wektor(a.dx + b.dx, a.dy + b.dy);
	}
	
	public void wypisz(){
		
		System.out.printf("[%.2f ,%.2f]\n",dx,dy);
	}

}
