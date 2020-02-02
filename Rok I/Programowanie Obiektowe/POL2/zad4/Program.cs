using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication5
{
    class Program
    {
        static void Main(string[] args)
        {
            ListaLeniwa przyklad = new ListaLeniwa();
            przyklad.init();
            Console.WriteLine(przyklad.size());
            Console.WriteLine(przyklad.element(5));
            Console.WriteLine(przyklad.element(135));
            Console.WriteLine(przyklad.element(5));
            Console.WriteLine(przyklad.size());
            Console.WriteLine("*************************************************");

            Pierwsze asd = new Pierwsze();
            asd.init();
            Console.WriteLine(asd.size());
            Console.WriteLine(asd.element(5));
            Console.WriteLine("----");

            for (int t=0; t<10; t++)
               Console.WriteLine(asd.element(t));

            Console.WriteLine("----");
            Console.WriteLine(asd.element(5));
            Console.WriteLine(asd.size());
            Console.ReadLine();

        }
    }

    class ListaLeniwa
    {
        List<int> T = new List<int>();
        int ilosc = 0;
        Random l = new Random();
        public void init()
        {
            ilosc = 0;
            T = new List<int>();
            l = new Random();
        }

        protected virtual int losowa(int x)
        {
            return l.Next();
        }

        public int element(int i)
        {
            if (i < ilosc)
                return T[i];
            else
            {

                for (int k = ilosc; k <= i; k++)
                {
                    T.Add(losowa(k));

                }
                ilosc = i+1;

            }
            return T[i];
        }


        public int size()
        {
            return ilosc;
        }

    }
    class Pierwsze : ListaLeniwa
        {
            protected bool pierwsza(int p)
            {
                if (p < 2)
                    return false;
                bool x = true;
                for (int d = 2; d <= Math.Sqrt(p); d++)
                {
                    if ((p % d) == 0)
                        x = false;
                }
                return x;
            }

            protected override int losowa(int zm)
            {
            int k = 2;
                while (zm!=0)
                {
                    k += 1;
                    if (pierwsza(k))
                    {
                         zm -= 1;
                    }
                }
                return k;
            }
       }
}


