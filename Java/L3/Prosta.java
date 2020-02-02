package geometria;

public class Prosta{
	
	public final double a;
	public final double b;
	public final double c;
	
	public Prosta(double a1, double b1, double c1){
		a = a1;
		b = b1;
		c = c1;
	}
	
	public static Prosta przesunP(Prosta p, Wektor v){

		double nc = p.c + v.dy;
		nc = nc - (p.a * v.dx); 

		return new Prosta(p.a,p.b,nc);
	}
	
	public static boolean rownolegle(Prosta p1, Prosta p2){
		return (p1.a * p2.b == p2.a * p1.b); 
	}
	
	public static boolean prostopadle(Prosta p1, Prosta p2){
		return (p1.a * p2.a == (-p1.b) * p2.b);
	}
	
	public static Punkt przeciecie(Prosta p1, Prosta p2) {
		double W = (p1.a * p2.b) - (p2.a * p1.b);
		double Wx = (-p1.c * p2.b) - (-p2.c * p1.b);
		double Wy = (p1.a * -p2.c) - (p2.a * -p1.c);
		
		return new Punkt(Wx/W, Wy/W);
	}
	public void wypisz(){
		System.out.printf("(%.2f x + %.2f y + %.2f)\n",a,b,c);
	}
}
