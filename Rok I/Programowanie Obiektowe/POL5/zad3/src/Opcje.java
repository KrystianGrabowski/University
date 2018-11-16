class Dodaj implements Wyrazenie
{
	Wyrazenie x;
	Wyrazenie y;
	public Dodaj (Wyrazenie a, Wyrazenie b)
	{
		x = a;
		y = b;
	}
	public int Oblicz()
	{
		return x.Oblicz() + y.Oblicz();
	}
	public String toString()
	{
		return "(" + x + "+" +y + ")";
	}
}
class Odejm implements Wyrazenie
{
	Wyrazenie x;
	Wyrazenie y;
	public Odejm (Wyrazenie a, Wyrazenie b)
	{
		x = a;
		y = b;
	}
	public int Oblicz()
	{
		return x.Oblicz() - y.Oblicz();
	}
	public String toString()
	{
		return "(" + x + "-" +y + ")";
	}
}
class Pomnoz implements Wyrazenie
{
	Wyrazenie x;
	Wyrazenie y;
	public Pomnoz (Wyrazenie a, Wyrazenie b)
	{
		x = a;
		y = b;
	}
	public int Oblicz()
	{
		return x.Oblicz() * y.Oblicz();
	}
	public String toString()
	{
		return "(" + x + "*" +y + ")";

	}
}
class Podziel implements Wyrazenie
{
	Wyrazenie x;
	Wyrazenie y;
	public Podziel (Wyrazenie a, Wyrazenie b)
	{
		x = a;
		y = b;
	}
	public int Oblicz()
	{
		return x.Oblicz() / y.Oblicz();
	}
	public String toString()
	{
		return "(" + x + "/" +y + ")";
	}
}