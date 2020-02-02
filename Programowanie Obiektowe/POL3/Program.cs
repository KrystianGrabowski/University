using System;

public class Elementy<T>
{
    public Elementy<T> nastepny = null;
    public Elementy<T> poprzedni = null;
    public T wartosc;

    public Elementy(T w)
    {
        this.wartosc = w;
    }
}

public class Lista<T>
{
    Elementy<T> poczatek = null;
    Elementy<T> koniec = null;
    public void dodaj_na_poczatek(Elementy<T> liczba)
    {
        if(poczatek == null)
        {
            poczatek = liczba;
            koniec = liczba;
        }
        else
        {
            liczba.nastepny = poczatek;
            poczatek = liczba;
        }
        Console.WriteLine(poczatek.wartosc);
    }

    public void dodaj_na_koniec(Elementy<T> liczba)
    {
        if(koniec == null)
        {
            poczatek = liczba;
            koniec = liczba;
        }
        else
        {
            koniec.nastepny = liczba;
            liczba.poprzedni = koniec;
            koniec = liczba;
        }
    }

    public Elementy<T> usun_na_poczatku()
    {
        Elementy<T> x = poczatek;
        poczatek = poczatek.nastepny;
        poczatek.poprzedni = null;
        return x;

    }

    public Elementy<T> usun_na_koncu()
    {
        Elementy<T> x = koniec;
        koniec = koniec.poprzedni;
        koniec.nastepny = null;
        return x;
    }
}

public class Program
{
    public static void Main()
    {
        Elementy<int> a = new Elementy<int>(5);
        Lista<int> s = new Lista<int>();
        s.dodaj_na_poczatek(a);
        Console.ReadLine();
    }
}