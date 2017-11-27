import java.awt.Color;
import java.awt.Point;

public class Kreska {
	public Point poczatek, koniec;
	public final Color kolor;
	
	public Kreska (Point pocz, Point kon, Color kol) {
		this.poczatek = pocz;
		this.koniec = kon;
		this.kolor = kol;
	}
}
