package wyrazenia;

public abstract class Wyrazenie {
/**
 * Klasa główna wyrażęnia
 */

	public abstract double oblicz();
	
	/** metoda sumująca wyrażenia */
	public static double sumuj (Wyrazenie[] wyr) {
		
		double suma = 0;
		
		System.out.println(wyr.length);
		for (int i = 0; i < wyr.length; i++){
			suma += wyr[i].oblicz();
		}
		
		return suma;
		
	}
	/** metoda mnożąca wyrażenia */
	public static double pomnoz (Wyrazenie[] wyr) {
		
		if(wyr.length>1){
		
			double iloczyn = wyr[0].oblicz();
		
			for (int i = 1; i < wyr.length; i++) {
				iloczyn *= wyr[i].oblicz();
			}
			return iloczyn;		
		
		}
		return 0;

	}

	
}
