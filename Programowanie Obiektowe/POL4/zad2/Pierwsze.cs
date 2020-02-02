using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace ConsoleApplication17
{
    class PrimeCollection : IEnumerable
    {
        public IEnumerator GetEnumerator()
        {
            return new Pierwsza();
        }

    }

    public class Pierwsza : IEnumerator
    {
        int licznik = 1;
        protected bool pierwsza(int p)
        {
            if (p < 2)
                return false;
            else
                for (int i = 2; i <= p / 2; i++)
                {

                    if (p % i == 0) return false;
                }
            return true;
        }
        public bool MoveNext()
        {
            licznik++;
            while (pierwsza(licznik) == false && licznik < int.MaxValue)
            {
                licznik++;
            }
            if (licznik < int.MaxValue)
                return true;
            return false;
        }
        public object Current
        {
            get
            {
                return licznik;
            }
        }
        public void Reset()
        {
            licznik = 1;
        }
    }
}
