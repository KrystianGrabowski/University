using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace ConsoleApplication17
{
    class Program
    {
        static void Main(string[] args)
        {
            PrimeCollection pc = new PrimeCollection();
            foreach (int p in pc)
            {
                Console.WriteLine(p);

            }
        }
    }



}
