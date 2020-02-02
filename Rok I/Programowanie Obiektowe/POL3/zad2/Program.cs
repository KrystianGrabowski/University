using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace ConsoleApplication8
{
    class Program
    {
        static void Main(string[] args)
        {
            Slownik<string, int> slow = new Slownik<string, int>();
            slow.Dodaj("ala", 3);
            slow.Dodaj("kot", 123);
            slow.Dodaj("krzys", 1211231231);
            slow.Dodaj("stanislaw", 231);
            Console.WriteLine("{0}, {1}", "ala", slow.Szukaj("ala"));
            slow.Usun("ala");
            slow.Dodaj("krzys", 1211231231);
            Console.WriteLine("{0}, {1}", "krzys", slow.Szukaj("krzys"));
            Console.WriteLine("{0}, {1}","ala -",slow.Szukaj("ala"));
            Console.WriteLine(slow.Szukaj("stasko"));
            Console.ReadLine();
        }


        class Slownik<K, V> where K : IComparable<K>
        {
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
            public V Szukaj(K haslo)
            {
               
                if ((this.klucz != null) && (this.klucz.CompareTo(haslo) == 0))
                    return wartosc;
                    
                else
                {
                    if (this.prev != null)
                        return this.prev.Szukaj(haslo);
                    else if (this.next != null)
                        return this.next.Szukaj(haslo);

                    else
                    {
                        Console.Write("Nie ma takiego elementu - ");
                        return wartosc;
                    }
                }
            }

            public void Usun(K uslo)
            {
                if (this.klucz.CompareTo(uslo) == 0)
                {
                    this.klucz = default(K);
                    this.wartosc = default(V);

                }
                else
                {
                    if (this.prev != null)
                        this.prev.Usun(uslo);
                    if (this.next != null)
                        this.next.Usun(uslo);
                }
            }


        }
    }

}