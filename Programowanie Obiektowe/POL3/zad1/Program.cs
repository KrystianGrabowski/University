using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication11
{
    class Program
    {
        static void Main(string[] args)
        {

           Lista<int> L = new Lista<int>();
//            Console.WriteLine(L.Pusta());
//            L.DodajP(231);
//            L.DodajK(231);
//            L.DodajK(231);
//            L.DodajK(231);
//            L.UsunK();
//            L.UsunP();
 //           L.UsunP();
//            Console.WriteLine(L.Pusta());
//            L.UsunP();
//            Console.WriteLine(L.Pusta());
//            Console.ReadLine();
//        }
    }
    public class Nielista<T>
    {
       
       public Nielista<T> next ;
       public Nielista<T> prev ;
       public T val;
    }
    public class Lista<T> : Nielista<T>
    {
            Nielista<T> lis = new Nielista<>(); 
            static int p;
           // public T val;
        public void DodajK (lis, val)
        {
            if (this.lis != null)
                lis.next = lis.val;

            else
            {
                p = p + 1;
                lis.next = val;
            }
        }
 /*       public void DodajP (lis val)
            {
                if (lis.prev != null)
                    lis.prev = val;

                else
                {
                    p = p + 1;
                    lis.prev = val;
                }
            }

           public void UsunP()
       {
           if (p > 0)
          {
               if ((this.prev == null) && (this.val != null))
               {
                  p = p - 1;
                   this.val = default(T);
             }

                else
                   this.prev.UsunP();
           }
            else
                Console.WriteLine("Nie ma czego usuwac");


        }
        public void UsunK()
        {
            if (p > 0)
            {
                if ((this.next == null) && (this.val != null))
                {
                    this.val = default(T);
                    p = p - 1;
                }

                else
                    this.next.UsunK();

            }
            else
                Console.WriteLine("Nie ma czego usuwac");

        }
        
        public bool Pusta()
        {
            return (p == 0);
      */  }
    }
}
