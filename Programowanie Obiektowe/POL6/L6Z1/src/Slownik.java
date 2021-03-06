import java.io.File;
import java.io.Serializable;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;
import java.util.Scanner;

class Slownik<K extends Comparable<K>, V> implements Serializable
        {
			private static final long serialVersionUID = 1L;
			Slownik<K, V> next;
            Slownik<K, V> prev;
            private K klucz;
            private V wartosc;
            public void Dodaj(K e1, V e2)
            {
                if (this.next == null && this.prev == null)
                {
                    klucz = e1;
                    wartosc = e2;
                    this.prev = new Slownik<K, V>();

                    this.next = new Slownik<K, V>();
                }
                else
                {
                    if (this.prev == null)
                        this.prev = new Slownik<K, V>();
                    this.prev.Dodaj(e1, e2);

                    if (this.next == null)
                        this.next = new Slownik<K, V>();
                    this.next.Dodaj(e1, e2);
                }
            }
            public void Wypisz()
            {
            	while (this.next != null)
            	{

            		System.out.print(this.klucz + " " +  this.wartosc);
            		System.out.print("\n");
            		this.klucz = this.next.klucz;
            		this.wartosc = this.next.wartosc;
            		this.next = this.next.next;

            	}
            }
            public V Szukaj(K haslo)
            {
               
                if ((this.klucz != null) && (this.klucz.compareTo(haslo) == 0))
                    return wartosc;
                    
                else
                {
                    if (this.prev != null)
                        return this.prev.Szukaj(haslo);
                    else if (this.next != null)
                        return this.next.Szukaj(haslo);

                    else
                    {
                        System.out.printf("Nie ma takiego elementu - ");
                        return wartosc;
                    }
                }
            }
            public void Usun(K uslo)
            {
                if (this.klucz.compareTo(uslo) == 0)
                {
                    this.klucz = this.next.klucz;
					this.wartosc = this.next.wartosc;
					this.next = this.next.next;

                }
                else
                {
                    if (this.prev != null)
                        this.prev.Usun(uslo);
                    if (this.next != null)
                        this.next.Usun(uslo);
                }
            }
            public String toString()
            {
            	String zbior = "";
            	while (this.next != null)
            	{

            		zbior = zbior + this.klucz+ " " + this.wartosc + " ";
            		zbior = zbior + "\n";
            		this.klucz = this.next.klucz;
            		this.wartosc = this.next.wartosc;
            		this.next = this.next.next;

            	}
            	return zbior;
            }
            public void WriteToFile() throws FileNotFoundException
            {
            	PrintWriter zapis = new PrintWriter("Slownik.txt");
            	String a = toString();
            	zapis.print(a);
            	zapis.close();
            }

            public Slownik ReadFromFile(String Name)throws FileNotFoundException
            {
            	Slownik <String,Integer> pomoc = new Slownik <String,Integer>();
      	      File file = new File(Name);
    	      Scanner in = new Scanner(file);
    	      String zdanie = in.nextLine();
    	      while (in.hasNext())
    	      {
    	    	  String T[] = zdanie.split(" ");
    	    	  int w = Integer.valueOf(T[1]);
    	    	  String t = T[0];
    	    	  pomoc.Dodaj(t, w);
    	    	  zdanie = in.nextLine();
    	 
    	      }
    	      String T[] = zdanie.split(" ");
    	      int w = Integer.valueOf(T[1]);
	    	  String t = T[0];
	    	  pomoc.Dodaj(t, w);
    	      in.close();
    	      return pomoc;
    	      

    	  
            }



}