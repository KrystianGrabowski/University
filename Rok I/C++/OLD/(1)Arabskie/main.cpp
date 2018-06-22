#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

string rzym,Rm;
int wynik;
const char* x;

const int B[] = {1000,
900, 500, 400, 100,
90, 50, 40, 10,
9, 5, 4, 1};
const string R[] = {"M",
"CM", "D", "CD", "C",
"XC", "L", "XL", "X",
"IX", "V", "IV", "I"};

int arab2bin (const char* x)
{   int i = 0;
    if (x[i] == '0')
    {
        cerr << "Liczba zaczyna sie od zera !";
        return 0;
    }

    while(x[i]!='\0')
        {
        if ((int(x[i])<48) || (int(x[i])>57))
            {cerr << "Podaj tylko liczby !";
            return 0;}
        i++;
        }
    if (i > 4)
    {
    cerr << "Liczba wieksza niz 4 znaki!";
    return 0;
    }

    return atoi(x);
}

string bin2rzym (int x)
{
    int i = 0;
    if ((x <= 3999) && (x > 0))
    {
    while (x>0){
        if (B[i] <= x){
            Rm += R[i];
            x -= B[i];
        }else
            i++;
        }
    }else if (x>3999)
    {
        int p = x;
        p = x/1000;
        x = x -(p*1000);
        if (p==5)
            cout << "_" << endl;
        else if (p==8)
            cout << "___" << endl;
        else
            cout << "__" << endl;

        bin2rzym(p);
        bin2rzym(x);

    }
    return Rm;
}

int main(int argc, const char ** argv)
{
    cout << "Zamiana liczb arabskich na rzymskie" << endl;
    for (int l=1; l<argc; l++)
    {
        wynik = arab2bin(argv[l]);
        if (wynik == 0)
            cerr << "(Blad)" << " <------- " << argv[l];
        else
        {
        rzym = bin2rzym(wynik);
        cout << rzym << " <------- " << argv[l] << endl;
        Rm = "";
        }
    }
    return 0;
}
