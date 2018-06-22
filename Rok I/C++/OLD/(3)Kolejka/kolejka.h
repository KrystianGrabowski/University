#include <iostream>
using namespace std;

class Kolejka
{
public:
    string *T;
    int pojemnosc;
    int ile;
    int poczatek;
public:

    Kolejka(int);
    Kolejka();
    Kolejka(initializer_list<string> v);
    Kolejka(Kolejka &kole);
    Kolejka & operator=(Kolejka &ex);
    Kolejka(Kolejka &&ko);
    Kolejka & operator=(Kolejka && exx);
    ~Kolejka();
    void wypisz();

    void wstaw(string elem);
    string pobierz();
    string sprawdz();
    int rozmiar();
};
