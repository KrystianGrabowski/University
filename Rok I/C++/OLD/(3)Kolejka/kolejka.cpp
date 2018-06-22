#include <iostream>
#include "kolejka.h"
using namespace std;

Kolejka::Kolejka(int l)
{
    pojemnosc = l;
    ile = 0;
    poczatek = 0;
    T = new string[pojemnosc];
}
Kolejka::Kolejka()
{
    pojemnosc = 4;
    ile = 0;
    poczatek = 0;
    T = new string[pojemnosc];

}
Kolejka::Kolejka( initializer_list<string> v)
{
    pojemnosc = v.size();
    T = new string[pojemnosc];
    int o = 0;
    for (string i : v)
    {
        T[o] = i;
        o++;
    }

    ile = v.size();
    poczatek = 0;
}

Kolejka::Kolejka(Kolejka  &kopia)
{
    pojemnosc = kopia.pojemnosc;
    T = new string[pojemnosc];
    ile = kopia.ile;
    poczatek =  kopia.poczatek;
    for (int i=0; i<pojemnosc; i++)
        T[i] = kopia.T[i];
}
 Kolejka & Kolejka:: operator=(Kolejka &ex)
{
    pojemnosc = ex.pojemnosc;
    T = new string[pojemnosc];
    ile = ex.ile;
    poczatek =  ex.poczatek;
    for (int i=0; i<pojemnosc; i++)
        T[i] = ex.T[i];
    return *this;
}
Kolejka::Kolejka(Kolejka &&ko)
{
    cout<<"pan kopiujacy";
    pojemnosc = ko.pojemnosc;
    ile = ko.ile;
    poczatek = ko.poczatek;
    T = ko.T;
    ko.T = nullptr ;
}
Kolejka & Kolejka :: operator=(Kolejka && exx)
{
   pojemnosc = exx.pojemnosc;
    T = new string[pojemnosc];
    ile = exx.ile;
    poczatek =  exx.poczatek;
    for (int i=0; i<pojemnosc; i++)
        T[i] = exx.T[i];
    exx.T = nullptr ;
    exx.ile = 0;
    exx.poczatek = 0;
    exx.pojemnosc = 0;
    return *this;
}

void Kolejka::wstaw(string elem)
{
    if (ile == pojemnosc)
            cout << "Kolejka jest pelna" << endl;
    else
    {
        T[ile] = elem;
        ile++;
    }

}
void Kolejka::wypisz()
{
if (T != nullptr)
{
    int i = 0;

    while(T[i]!= "" && i+1 < ile )
    {
        i++;
    }
    while (i >= 0)
    {
        cout << "("<<i<<")" << " Element to : " << T[i]<<endl;
        i--;

    }}
else
    cout << "Kolejka nie istnieje: "<<endl;
}

string Kolejka::sprawdz()
{
    if (ile != 0)
    {
        return T[ile-1];
    }
    else
        return "Kolejka Pusta !";
}
string Kolejka::pobierz()
{
    string pom;
    if (ile != 0)
    {
    pom = T[ile-1];
    T[ile-1] = "";
    ile --;
    }
    else
        pom = "Kolejka Pusta ! ";
        return pom;

    return pom;

}

int Kolejka::rozmiar()
{
    return ile;
}


Kolejka::~Kolejka()
{
    cout << "Des";
    delete [] T;
}
