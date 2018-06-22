
public abstract class StPolicja implements Comparable<StPolicja>
	{
	public String Nazwisko;
	public abstract int Waga();
	public abstract String Stopien();
	public int compareTo(StPolicja St)
	{
		if (this.Waga() < St.Waga())	{return -1;}
		else if	(this.Waga() == St.Waga()) {return 0;}
		else {return 1;}
	}
	public String toString()
	{
		return "Nazwisko: " + Nazwisko + " || " + " Stopien: " + Stopien() + "(" + Waga() + ")";
	}
	}
