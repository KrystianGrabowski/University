
import java.io.IOException;

public class Main {

	public static void main(String[] args) throws InterruptedException, IOException  {
		/*Ksiazka k = new Ksiazka("Mickiewicz", "Dziady", 1234);
		System.out.print(k.toString());
		k.Edycja();
		System.in.read();
		System.out.print(k.toString());
		
		WydawnictwoCiagle k3 = new WydawnictwoCiagle("Mickiewicz", "Dziady", 1234);
		System.out.print(k3.toString());
		k3.Edycja();
		System.in.read();
		System.out.print(k3.toString());*/
		
		Czasopismo k2 = new Czasopismo("Mickiewicz", "Dziady", 1234);
		System.out.print(k2.toString());
		k2.Edycja();
		System.in.read();
		System.out.print(k2.toString());
	}

}
