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
            Console.WriteLine(L.Pusta());
            L.DodajP(23122222);
            Console.WriteLine(L.UsunP());
            Console.WriteLine(L.Pusta());
            //L.DodajP(312313);

           // Console.WriteLine(L.UsunK());
           // Console.WriteLine(L.UsunK());
           // Console.WriteLine(L.UsunK());
           // Console.WriteLine(L.UsunK());
           // Console.WriteLine(L.UsunK());
           // Console.WriteLine(L.Pusta());

            Console.ReadLine();
         
        }
        public class Inna<T>
        {

            public Inna<T> next = null;
            public Inna<T> prev = null;
            public T val;
        }
        public class Lista<T>
        {
            Inna<T> glowa = null;
            Inna<T> ogon = null;
            public void DodajK(T w)
            {
                if (ogon == null)
                {
                    ogon = new Inna<T>();
                    ogon.val = w;
                    glowa = ogon;
                   
                }
                else
                {
                    Inna<T> x = new Inna<T>();
                    x.val = w;
                    ogon.next = x;
                    x.prev = ogon;
                    ogon = x;
                }
            }
            public void DodajP(T w)
            {
                if (glowa == null)
                {
                    glowa = new Inna<T>();
                    glowa.val = w;
                    ogon = glowa;
                }

                else
                {
                    Inna<T> x = new Inna<T>();
                    x.val = w;
                    glowa.next = x;
                    x.prev = glowa;
                    glowa = x;
                }
            }
            
           public T UsunP()
       {
                if (glowa != null)
                {
                    T val = glowa.val;
                    glowa.val = default(T);
                    glowa = glowa.next;
                    return val;
                }
                
                else
                {
                    Console.WriteLine("Pusta Lista");
                    return default(T);
                }
        }   
        public T UsunK()
        {
                if (ogon != null)
                {
                    T val = ogon.val;
                    ogon.val = default(T);
                    ogon = ogon.next;
                    return val;
                }

                else
                {
                    Console.WriteLine("Pusta Lista");
                    return default(T);
                }
            }
        
        public bool Pusta()
        {
                if ((ogon == null) && (glowa == null))
                    return true;
                return false;
        }
           
        
        }
    }
}
