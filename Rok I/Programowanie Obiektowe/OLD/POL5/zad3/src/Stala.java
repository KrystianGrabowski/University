
public class Stala implements Wyrazenie
{
	int wartosc;
	
	public Stala (int n)
	{
		wartosc = n;
	}
	public int Oblicz()
	{
		return wartosc;
	}
	public String toString()
	{
		return "" + wartosc;
	}
}
