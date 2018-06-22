using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication4
{
    class Program
    {
        static void Main(string[] args)
        {
            IntStream obj = new IntStream();
            Console.WriteLine("******************************************");
            for (int i=0; i<7; i++)              // kolejne naturalne
            Console.WriteLine(obj.next());
            obj.reset();
            Console.WriteLine(obj.eos());
            for (int i = 0; i < 5; i++)        
            Console.WriteLine(obj.next());       //kolejne naturalne

            Console.WriteLine("******************************************");
            PrimeStream pierw = new PrimeStream();      //pierwsze
            for (int i=0; i<10; i++)
            {
               Console.WriteLine(pierw.next());
            }
            pierw.reset();
            Console.WriteLine(pierw.eos());
            Console.WriteLine(pierw.next());           //pierwsze

            Console.WriteLine("******************************************");
            RandomStream los = new RandomStream();    //losowe
            for (int i = 0; i < 12; i++)
                System.Console.WriteLine(los.next());
            System.Console.WriteLine(los.eos());             //losowe
                                                                           
                Console.WriteLine("******************************************");
            RandomWordStream wyr = new RandomWordStream();          //randomowe slowa pierwsze
            for (int i = 0; i < 12; i++)
                Console.WriteLine(wyr.next());                      //randomowe slowa pierwsze
            Console.WriteLine("******************************************");
            Console.ReadLine();

        }
    }
    public class IntStream
    {
        public int l = -1;
        public virtual int next()
        {
            if (eos() == true)
                return -1;
            l++;
            return l;
        }
        public bool eos()
        {
            if (l >= int.MaxValue)
                return true;
            return false;
        }

        public void reset()
        {
         l = -1;
        }
    }

    public class PrimeStream : IntStream
    {
        int p;
        public bool pierwsza(int p)
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

        public override int next()
        {
            if (eos() == true) return -1;
            l++;
            while (pierwsza(l) == false)
                l++;
            if (eos() == true) return -1;
            else return l;
        }

 }
    public class RandomStream : IntStream
    {
            Random los = new Random();
            public  override int next()
            {
                return los.Next();
            }


    }
    public class RandomWordStream :  PrimeStream
    {
        RandomStream los = new RandomStream();
        public new string next()
        {
            int a;
            base.next();
            string w = "";
            for (int o=0; o<l; o++)
            {
                w += char(los.next() % 256);

            }


            return w;
        }
    }
}




