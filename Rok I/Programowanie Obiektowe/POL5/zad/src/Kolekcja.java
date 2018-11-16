
public class Kolekcja <K, T extends Comparable<T>>
{
	K key;
	T value;
	Kolekcja<K,T> next;
	public Kolekcja () {}
	public Kolekcja(K key, T value)
	{
		this.key = key;
		this.value = value;
		this.next = null;
	}
	public Kolekcja<K ,T> Pobierz()
	{
		Kolekcja<K, T> wsk = this.next;
		if(this.next == null) 
			System.out.println("Koniec Kolekcji");
		else
			this.next = this.next.next;
		return wsk;			

	}
	public void Dodaj(K key, T value)
	{
		
		if(this.next==null)
		{
			this.next = new Kolekcja<K,T>(key,value);
		}
		else 
		{
			if (this.next.value.compareTo(value)<=0)
			{
				this.next.Dodaj(key, value);
			}
			else
			{
				Kolekcja<K,T> n = this.next;
				this.next = new Kolekcja<K,T>(key,value);
				this.next.next = n;
			}
		}
	}
	public void Wypisz()
	{

		if (this.next != null)
		{
			System.out.println(this.next.key + " " + this.next.value);
			this.next.Wypisz();
		}
	}
	

}
