package geometria;


public class Punkt{

	protected double x;
	protected double y;
	
	public Punkt(double a, double b){
		x = a;
		y = b;
	}

	public void przesun(Wektor v){
		x = v.dx + x;
		y = v.dy + y;
	
	}
	

	
	public void obroc(Punkt p, double kat){
		double x1 = (x - p.x) * Math.cos(Math.toRadians(kat)) - (y - p.y) * Math.sin(Math.toRadians(kat)) + p.x;
		double y1 = (x - p.x) * Math.sin(Math.toRadians(kat)) + (y - p.y) * Math.cos(Math.toRadians(kat)) + p.y;

		x = x1;
		y = y1;
	}
	//
	public void odbij(Prosta p) {
		double na, nb, nc;
		double ap, bp, cp;
		if (p.b != 0){
			na = p.a / (-p.b);
			nb = 1;
			nc = p.c / (-p.b);			
		}
		else{
			na = p.a;
			nb = 0;
			nc = p.c;
		}

		if (na != 0){
			ap = (-1 / na);
			cp = y - (ap * x);
		}
		else {
			ap = 0;
			cp = y - (ap * x);
		}
		Prosta Prosta1 = new Prosta(ap,-1,cp);
		Punkt przec = Prosta.przeciecie(p,Prosta1);
		Punkt K = new Punkt(x,y);
		K.obroc(przec,180);
		x = K.x;
		y = K.y;
	}
	
	public void wypisz(){
		System.out.printf("(%.2f, %.2f)\n",x,y);
	}

}

