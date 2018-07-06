package geometria;
import static geometria.Wektor.*;
import static geometria.Prosta.*;

public class Main{

	public static void main(String []args){
		System.out.println("---------------- WEKTOR ----------------");
		Wektor v1 = new Wektor(2,4);
		Wektor v2 = new Wektor(4,1);
		zloz(v1,v2).wypisz();
		
		System.out.println("---------------- PROSTA ----------------");
		Prosta p1 = new Prosta(2,-1,-3);
		przesunP(p1, v1).wypisz();
		
		Prosta R1 = new Prosta(2,-1,2);
		Prosta R2 = new Prosta(2,-1,-1);
		System.out.println(rownolegle(R1,R2));
		
		Prosta Pr1 = new Prosta(-2,-1,-3);
		Prosta Pr2 = new Prosta((1/2.0),-1,-1);
		System.out.println(prostopadle(Pr1,Pr2));
		
		Prosta przec1 = new Prosta(1,-1,2);
		Prosta przec2 = new Prosta(-1,-1,2);
		przeciecie(przec1, przec2).wypisz();
		
		Prosta zprzec1 = new Prosta(5,0,-3);
		Prosta zprzec2 = new Prosta(0,-1,2);
		przeciecie(zprzec1, zprzec2).wypisz();
				
		System.out.println("####################### PRZESUN ------------------");
		System.out.println("---------------- Punkt ----------------");
		Wektor v66 = new Wektor(3,3);
		Punkt pkt1 = new Punkt(2,1);
		pkt1.przesun(v66);
		pkt1.wypisz();
		
		System.out.println("---------------- Odcinek ----------------");
		Odcinek odc1 = new Odcinek(1,2,3,3);
		odc1.przesun(v66);
		odc1.wypisz();
		
		System.out.println("---------------- Trójkąt ----------------");
		Trojkat tr1 = new Trojkat(1,1,1,3,2,4);
		tr1.przesun(v66);
		tr1.wypisz();
		
		System.out.println("####################### OBROT ------------------");
		int kat = 90;
		System.out.println("---------------- Punkt ----------------");
		Punkt pkt2 = new Punkt(0,3);
		Punkt zero = new Punkt(0,0);
		pkt2.obroc(zero,kat);
		pkt2.wypisz();
		
		System.out.println("---------------- Odcinek ----------------");
		Odcinek odc2 = new Odcinek(-3,0,-1,0);
		odc2.obroc(zero,kat);
		odc2.wypisz();
		
		System.out.println("---------------- Trójkąt ----------------");
		Trojkat tr2 = new Trojkat(-3,0,-1,0,-2,2);
		tr2.obroc(zero, kat);
		tr2.wypisz();
		
		System.out.println("####################### ODBICIE ------------------");

		System.out.println("---------------- Punkt ----------------");
		Prosta xzero = new Prosta(1,0,1);
		Punkt pkt3 = new Punkt(1,2);

		pkt3.odbij(xzero);
		pkt3.wypisz();
		System.out.println("---------------- Odcinek ----------------");
		Odcinek odc3 = new Odcinek(1,2,4,2);
		odc3.odbij(xzero);
		odc3.wypisz();
		
		System.out.println("---------------- Trójkąt ----------------");
		Trojkat tr3 = new Trojkat(1,3,3,3,8,8);
		tr3.odbij(xzero);
		tr3.wypisz();
		
		
		
		
		

	
	
	
	
	
	
	
		/*Prosta pr2 = new Prosta(2,0,-2);
		Prosta pr1 = new Prosta(0,2,0);
		Punkt p1 = Prosta.przeciecie(pr1,pr2);
		p1.wypisz();
		System.out.println("Uwtorzyłem chyba Punk1");
		Trojkat o2 = new Trojkat(3,3,3,3,4,4);

		Wektor w2 = new Wektor(3,3);
		Wektor w3 = Wektor.zloz(w,w2);
		w3.wypisz();
		Punkt p1 = new Punkt(3, 2);
		double kat = 30;
		p1.obroc(p1, kat);
				Prosta p1 = new Prosta(-2,-1,3);
		Wektor v = new Wektor(-2,1);
		Prosta p2 = Prosta.przesunP(p1,v);
		p2.wypisz();*/
		
	}
	


}
