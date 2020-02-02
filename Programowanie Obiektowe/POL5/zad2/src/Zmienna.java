import java.util.Hashtable;

public class Zmienna implements Wyrazenie
{
	String x; 
	Hashtable<String, Integer> Drzewo;
	
	public Zmienna(String y, Hashtable<String, Integer> l)
	{
		x = y; 
		Drzewo = l;
		
	}
	
	public int Oblicz() 
	{ 
		return Drzewo.get(x); 
	}
	public String toString()
	{
		return x; 
	}
}