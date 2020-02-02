#include <iostream>

class Lista
{
public :
    class Wezel;

private:
    Wezel *Pierwszy;
    Wezel *Ostatni;
    int Rozmiar;

protected:
    Wezel* ElPocz();
    Wezel* ElKon();
public:
    Lista();
    ~Lista();
    Lista(const Lista &E);
    Lista(Lista &&E);
    void Dodaj(int Indeks, double Wartosc);
    bool Usun(int Indeks=0);
    virtual void Wypisz();
    bool Pusta();
    int Rozmiar_W();
    double Przod();
    double Tyl();
    Lista& operator =(const Lista &E);
    Lista& operator =(Lista &&E);

    friend std::ostream& operator<<(std::ostream &W, const Lista &E);


};

class Lista::Wezel
{
public:
    double Wartosc;
    Wezel *Nastepny;
    Wezel *Poprzedni;

    Wezel() : Nastepny(nullptr), Poprzedni(nullptr){;}

    void* operator new(size_t MemSize);
	void operator delete(void* Usuwany);

};

class Kolejka:private Lista
{
public:
    void operator+=(double Wartosc);
    bool operator--();
    void Wypisz();
    Wezel* GT();
    Wezel* operator*();

};

class Stos:private Lista
{
public:
    void operator+=(double Wartosc);
    bool operator--();
    void Wypisz();
    Wezel* GT();
    Wezel* operator*();

};
